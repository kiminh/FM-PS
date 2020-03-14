import logging
import numpy as np
import sys
sys.path.append("../src/exception")
sys.path.append("..")

#序列化结构
from dataloader.data_handler import * 

#thrift RPC调用
from task import MLtask
from task.ttypes import *
from task.constants import *

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
    self.parameter_client_list = None
    self.server_group = None
    self.task = None
    self.network = None
    self.data = None
    #记录现在训练到第几个epoch
    self.epoch = None
    self.gradient = dict()
    self.parameters = dict()
    self.data_handler = None

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
    self.id = self.master_client.worker_regist_to_master("")
    logger.info("id: "+self.id)

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
      #目前想法：只要字节流长度大于0就看作有任务
      #判断任务
      if len(task) <= 0:
        continue
      #解析任务
      if not self.task.ParseFromString(task):
        logger.error("反序列化任务失败")
      if self.task.HasField('dataset'):
        logger.info("收到任务中的数据集为"+self.task.dataset)
      if self.task.HasField('data_path'):
        logger.info("收到任务中的数据路径为"+self.task.data_path)
      #判断任务
      break

  #动态构建神经网络保存到self.network
  #以及建立self.parameters和self.gradient的映射(key->对应shape和data_type的ndarray)
  def set_training_env(self):
    #建立层
    layer_list = []
    for layer in self.task.layers:
      #对于每一层需要做两件事
      #一是动态建立网络层对象
      #而是保存其中的参数key,shape,data_type建立key->value(ndarray)的工作
      #两个映射,一个是为了接收来自server的参数值，能够替换当前网络的所有参数
      #二是要建立梯度，即push的内容
      name = layer.name
      #TODO
      if name == "Input":
        #对于输入层来说，只需要知道输入的shape
        pass
      #TODO 可以抽象出一个函数
      elif name == "Dense":
        #要构建全连接层只需要知道输出size和激活函数
        activation = layer.activation
        output_size = None
        #参数列表
        for parameter in layer.parameter_list:
          parameter_name = parameter.name
          #TODOdata_type
          parameter_shape = parameter.shape
          #建立参数和梯度的空数组
          self.gradient[parameter_name] = np.zeros(shape)
          self.parameters[parameter_name] = np.zeros(shape)
          #对于全连接层的output_size
          #TODO目前是二维
          if parameter.dim == 2:
            output_size = parameter_shape[1]
        layer_list.append(FullConnected(output_size, activation))
    #所有层都添加后就可以建立网络对象
    self.network = Network(layer_list)


  #根据self.task中的数据路径
  #以及任务划分模式
  #"average" = id * data_size / work_nums (可以算出起始位置)
  #有了路径，有了如何分配那么就可以把数据加载到self.data
  #同时根据路径不同文件格式解析训练数据
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
    

  #根据self.server_group中的信息建立一个客户端组
  #TODO思考如何确保连接是稳定且符合预期
  def connect_to_server(self):
    #该函数的关键仍然在于确保与每一个server只建立一次客户端并且成功的连接
    #拿到应该建立的服务器组信息
    self.server_group = self.task.servers
    #如果客户端列表个数已经建立了对应的客户端那么就退出
    if len(self.parameter_client_list) == len(self.server_group):
      return
    for rank in range(len(server_group)):
      #建立客户端
      transport = TSocket.TSocket(server_group[rank].ip, server_group[rank].port)
      transport = TTransport.TBufferedTransport(transport)
      protocol = TBinaryProtocol.TBinaryProtocol(transport)
      self.parameter_client_list.append(ParameterServer.Client(protocol))
      transport.open()


  #key operation
  #通过客户端组向server group请求第t轮的参数
  #需要做一个整理到self.parameter
  def pull_parameter(self,t):
    serialized_parameter_list = []
    #对于每一个客户端都会拉回若干参数，需要将参数按key整理
    #先添加再整理
    for client in self.parameter_client_list:
      serialized_part_parameter = client.pull(t)
      serialized_parameter_list.appen(serialized_part_parameter)
    #每一个服务器都会返回一个序列化后的dict
    for part_parameter in serialized_parameter_list:
      pass
      #反序列化为一个protobuf对象
      #TODO定义该对象结构
      """
      protobuf_object = Object()
      protobuf_object.ParseFromString(part_parameter)
      #按key遍历
      for key in protobuf_object:
        value = ...
        #fit value into self.parameters
      """

  #将最新的参数self.parameters更新到self.network
  def fill_newest_parameter(self):
    pass

  #开始第t个epoch的训练
  #首先拉取参数，之后更新现有网络的参数，然后开始训练
  #保存第t轮的梯度到self.gradient
  def train(self,t):
    pass

  #将梯度根据self.server_group中的id进行分片
  #返回分组完成的梯度列表
  def slice_gradient():
    pass

  #key operation
  #通过slice_gradient完成的列表，客户端组发送梯度到连接的服务端
  def push_gradient(self):
    pass

  #将第t轮的forward结果传给master
  def evaluation(self,t):
    pass	


#worker需要什么：
"""
1.从脚本拉起之后要连接到master//
2.连接之后要进行注册拿到id//
3.要loop请求server信息以及任务//
4.拿到任务之后要建立网络，拿到数据，连接到所有server//
5.请求参数pull(half done)
6.计算
7.push梯度
8.evaluation 并返回结果给master
8.拿到下一轮参数
...
"""