import sys
sys.path.append("../tworker")
sys.path.append("..")
sys.path.append("../common")
sys.path.append("../common/gen-py")
sys.path.append("../network")

import logging
import numpy as np
import time

#网络结构
from network.layer import *
from new_network import *

#proto
from transport_info_pb2 import *
from parameter_server_pb2 import *

#序列化结构
from dataloader.data_handler import * 
from dataloader.my_data_loader import*

#thrift RPC调用
from task import MLtask
from task.ttypes import *
from task.constants import *

from parameter_server import ParameterServer
from parameter_server.ttypes import *
from parameter_server.constants import *

#thrift RPC客户端
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

logging.basicConfig(level=logging.INFO,
              format='%(asctime)s %(levelname)s '
              '%(filename)s:%(lineno)d; '
              '%(message)s')
logger = logging.getLogger(__name__)

#worker建立之初,可以通过main函数告诉该类master的ip和port

#Tworker职责在于拉取最新的参数，算出本轮梯度push到服务端
class Tworker(object):
  def __init__(self,master_ip,master_port):
    self.master_ip = master_ip
    self.master_port = master_port
    self.id = None
    #与master的客户端
    self.master_client = None
    #与一组server的客户端列表
    self.parameter_client_list = []
    self.server_group = None
    self.task = WorkerTask()
    self.network = None
    self.data = None
    #记录现在训练到第几个epoch
    self.epoch = None
    self.gradient = dict()
    self.parameters = dict()
    self.data_handler = None
    self.serialized_gradient = dict()

  def build_client_to_master(self):
    if self.master_client is None:
      transport = TSocket.TSocket(self.master_ip, self.master_port)
      transport = TTransport.TBufferedTransport(transport)
      protocol = TBinaryProtocol.TBinaryProtocol(transport)
      #建立客户端
      self.master_client = MLtask.Client(protocol)
    if transport.isOpen():
      raise RepeatedConnectError()
    transport.open()
    logger.info("成功建立客户端")
    #注册信息
    #master并不需要掌握worker的身份信息
    self.id = self.master_client.worker_regist_to_master()
    logger.info("id: " + str(self.id))

  #@para无
  #return 任务信息WorkerTask（内含一组需要连接的服务器）
  #需要保存到self.task以及self.server_group
  def ask_for_task(self):
  #循环请求任务，若任务为空则继续请求
  #TODO讨论,需要有什么措施吗，还是一直请求到有任务
    while True:
      #请求任务
      task = self.master_client.worker_ask_for_task()
  #任务包括什么：服务器信息+训练任务
      if len(task) <= 0:
        #目前做法进程挂起
        time.sleep(1)
        continue
      #解析任务
      if not self.task.ParseFromString(task):
        logger.error("反序列化任务失败")
        return
      if self.task.HasField('dataset'):
        logger.info("收到任务中的数据集为"+self.task.dataset)
      if self.task.HasField('data_path'):
        logger.info("收到任务中的数据路径为"+self.task.data_path)
      #判断任务
      break

  #动态构建神经网络保存到self.network
  #建立key->value的映射可以交给第一次pull参数时来做
  #TODO避免Magic number，将这里的命名规则与model进行统一组织
  def set_training_env(self):
    #建立层
    layer_list = []
    for layer in self.task.layers:
      #动态建立网络层对象
      name = layer.name
      #TODO
      if name == "Input":
        #对于输入层来说，只需要知道输入的shape
        layer_list.append(InputLayer((layer.output_size,)))
        print(name)
        print(layer.output_size)
      #TODO 可以抽象出一个函数
      elif name == "Dense":
        #要构建全连接层只需要知道输出size和激活函数
        activation = layer.activation
        output_size = layer.output_size
        activation_obj = None
        if activation == "Sigmoid":
          activation_obj = Sigmoid()
        elif activation == "SoftmaxLoss":
          activation_obj = SoftmaxLoss()
        layer_list.append(FullConnected(output_size, activation = activation_obj))
        print(name)
        print(output_size, activation)
    #所有层都添加后就可以建立网络对象
    self.network = Network(layer_list)
    print(self.network)

  def load_data(self):
    path = self.task.data_path
    dataset = self.task.dataset
    self.dataloader = DataLoader(path = path, dataset = dataset)
    self.data = self.dataloader.get_data()
    #TODO:添加处理其他数据集
    #training_data size
    logger.info(len(self.data[0][0]))
    #validation_data size
    logger.info(len(self.data[1][0]))
    #test_data size
    logger.info(len(self.data[2][0]))
    #TODO将数据整合my_data_loader合并进data_handler
    self.data = data_wrapper(self.data)

  #根据self.server_group中的信息建立一个客户端组
  #TODO思考如何确保连接是稳定且符合预期
  def connect_to_server(self):
    #该函数的关键仍然在于确保与每一个server只建立一次客户端并且成功的连接
    #拿到应该建立的服务器组信息
    self.server_group = self.task.servers
    logger.info("需要连接" + str(len(self.server_group)))
    #如果客户端列表个数已经建立了对应的客户端那么就退出
    if len(self.parameter_client_list) == len(self.server_group):
      return
    for rank in range(len(self.server_group)):
      #建立客户端
      transport = TSocket.TSocket(self.server_group[rank].ip, self.server_group[rank].port)
      transport = TTransport.TBufferedTransport(transport)
      protocol = TBinaryProtocol.TBinaryProtocol(transport)
      client = ParameterServer.Client(protocol)
      #需要确保server可连接
      while True:
        try:
          transport.open()
        except Thrift.TException as ex:
          continue
        self.parameter_client_list.append(client)
        logger.info("建立与参数服务器:"+self.server_group[rank].ip+" "+str(self.server_group[rank].port)+"的连接")
        break


  #key operation
  #通过客户端组向server group请求第t轮的参数
  #需要做一个整理到self.parameter
  #self.parameters:
  #嵌套字典
  #{  0 : {key,value}  }
  def pull_parameter(self,t):
    serialized_parameter_list = []
    #对于每一个客户端都会拉回若干参数，需要将参数按key整理
    #先添加再整理
    for client in self.parameter_client_list:
      serialized_part_parameter = client.pull(t)
      serialized_parameter_list.append(serialized_part_parameter)
    #每一个服务器都会返回一个序列化后的Key-value pair组
    for i in range(len(serialized_parameter_list)):
      #反序列化为一个protobuf对象
      parameter_from_one_server = ParametersOrGradients()
      parameter_from_one_server.ParseFromString(serialized_parameter_list[i])
      #对于每个客户端都要维护它自己的key
      #如果是第一次拉取参数那么需要建立
      dict_of_parameter_from_one_server = self.parameters.get(i, dict())
      for pair in parameter_from_one_server.pairs:
        values = np.array(pair.values).reshape(tuple(pair.shape))
        #print(pair.name)
        #print(values)
        dict_of_parameter_from_one_server[pair.name] = values
      self.parameters[i] = dict_of_parameter_from_one_server

  #将最新的参数self.parameters更新到self.network
  def fill_newest_parameter(self):
    for parameter_dict in self.parameters:
      for key in self.parameters[parameter_dict]:
        #example: Dense_w_2 第三层网络的权重参数
        key_infomation = key.split('_')
        pos = int(key_infomation[2])
        parameter_attr = key_infomation[1]
        values = self.parameters[parameter_dict][key]
        self.network.layers[pos].fill_parameters(values, parameter_attr, key)

  def train(self):
    logger.info("开始训练")
    #TODO抽象出这个处理过程
    start = self.id * 5000
    end = self.id * 5000 + 5000
    x_train = self.data[0][0][start:end]
    y_train = self.data[0][1][start:end]
    start = self.id * 500
    end = self.id * 500 + 500
    x_test = self.data[2][0][start:end]
    y_test = self.data[2][1][start:end]
    num_data = len(x_train)

    epoch = self.task.epoch
    mini_batch_size = self.task.mini_batch_size
    if 0:
      self.network.training(x_train,y_train, x_test, y_test, epoch, 0.3, mini_batch_size)
    else:
      print("epoch:",epoch)
      #对于每一轮训练来说
      for t in range(1,epoch+1):
        pack = list(zip(x_train,y_train))
        batches = [pack[j:j+mini_batch_size] for j in range(0,num_data,mini_batch_size)]
        #对于每个mini-batch
        #都要做以下步骤
        #pull最新的参数-》fill参数到神经网络结构-》产生最新的梯度-》抽取最新的梯度
        #打包为对应每个Pserver负责的部分-》push到参数服务器
        for mini_batch in batches:
          #拉取第t轮的参数
          self.pull_parameter(t)
          #fill parameters
          self.fill_newest_parameter()
          #执行forward和backward
          self.one_batch_forward_and_backward(mini_batch)
          #抽取参数到self.gradient
          self.get_gradient_from_network(mini_batch_size)
          #对于每一个Server拿到的无非是对应key的KeyValuePair列表
          #所以需要把每一个参数分到之前对应的服务器上
          self.slice_gradient()
          self.push_gradient(t)
        self.evaluation(t)

  def get_gradient_from_network(self, mini_batch_size):
    for i in range(len(self.network.layers)):
      #抽取每一个参数(key, gradients) pair to self.gradient
      if hasattr(self.network.layers[i], "w_name"):
        self.gradient[self.network.layers[i].w_name] = self.network.layers[i].one_batch_dw / mini_batch_size
        self.network.layers[i].one_batch_dw = 0
      if hasattr(self.network.layers[i], "b_name"):
        self.gradient[self.network.layers[i].b_name] = self.network.layers[i].one_batch_db / mini_batch_size
        self.network.layers[i].one_batch_db = 0

  #将梯度根据self.parameter中的rank进行分片
  #目的是产生分组完成并序列化的梯度列表
  def slice_gradient(self):
    #获取每个服务器拥有的key
    for key_dict in self.parameters:
      #如果有3个服务器，那么就是0,1,2
      #所以要有三个ParametersOrGradients对象
      gradient_pb = ParametersOrGradients()
      for key in self.parameters[key_dict]:
        gradient_pb.pairs.append(self.build_parameter(key))
      self.serialized_gradient[key_dict] = gradient_pb.SerializeToString()


  def one_batch_forward_and_backward(self, mini_batch):
    #每个batch包括training_data和one-hot vector label
    for x,t in mini_batch:
      y = self.network.feedforward(x)
      #loss 层 forward
      self.network.layers[-1](y, input_size = y.shape[0], t = t)
      self.network.backward()

  #key operation
  #通过slice_gradient完成的dict，客户端组发送梯度到连接的服务端
  def push_gradient(self,t):
    for client_rank in self.serialized_gradient:
      client = self.parameter_client_list[client_rank]
      client.push(t, self.serialized_gradient[client_rank])

  #产生指定key的PB对象
  def build_parameter(self, key):
    serialized_parameter = KeyValuePair()
    #key
    serialized_parameter.name = key
    # if key == "Dense_w_2":
    #   print(self.gradient[key].flatten()[:2])
    #平铺
    gradient = self.gradient[key]
    if gradient.ndim == 2:
      serialized_parameter.values.extend(gradient.flatten())
    else:
      serialized_parameter.values.extend(gradient)
    return serialized_parameter

  #将第t轮的forward结果传给master
  def evaluation(self,t):
    self.pull_parameter(t)
    self.fill_newest_parameter()
    start = self.id * 500
    end = self.id * 500 + 500
    x_test = self.data[2][0][start:end]
    y_test = self.data[2][1][start:end]
    self.network.evaluate(x_test, y_test)
