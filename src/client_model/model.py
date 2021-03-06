import logging

import sys
sys.path.append("../src/common")
sys.path.append("../common")
sys.path.append("../src/common/gen-py")
sys.path.append("../common/gen-py")
sys.path.append("../src/exception")

from exception import *

from transport_info_pb2 import*
from task import MLtask
from task.ttypes import *
from task.constants import *
 
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol



logging.basicConfig(level=logging.INFO,
              format='%(asctime)s %(levelname)s '
              '%(filename)s:%(lineno)d; '
              '%(message)s')
logger = logging.getLogger(__name__)

class Model(object):
  def __init__(self):
    #此为序列化后对象
    self.network_struct = None
    self.dist_info = None
    #Model内需要封装一个客户端，向Master提交任务并且接收计算结果
    self.task_client = None
    self.client_network = None
    self.client_hyperparameter = None
    self.hyperparameter = None

  #接收一个网络结构列表，逐层解析出网络结构信息，序列化到self.network_struct
  #self.network_struct是一个protobuf的序列化对象
  def set_network(self, network, hyperparameter):
    self.client_network = network
    self.set_layer_info_by_call()
    #网络信息设置好后各网络各自负责生成对应Layer的pb对象
    self.network_struct = NetworkStruct()
    self.network_struct.nums_layers = len(self.client_network)
    #TODO:存储网络的数据结构可能从list改为图    for i in range(len(self.client_network)):
      self.network_struct.layers.append(self.client_network[i].pb_layer)

    #超参数
    self.client_hyperparameter = hyperparameter
    self.network_struct.hparameter.optimizer = self.client_hyperparameter.optimizer
    self.network_struct.hparameter.learning_rate = self.client_hyperparameter.learning_rate
    self.network_struct.hparameter.mini_batch_size = self.client_hyperparameter.mini_batch_size
    self.network_struct.hparameter.epoch = self.client_hyperparameter.epoch
    self.network_struct.hparameter.loss = self.client_hyperparameter.loss

    #logger.info(self.network_struct)
    logger.info(self.network_struct)
    self.network_struct = self.network_struct.SerializeToString()


  #call 对应的layer来初始化权重shape等信息
  def set_layer_info_by_call(self):
    #输入层不需要,所以从第1层开始
    #此为可扩展可修改接口
    #但是每一层都要自我管理一个pb对象
    self.client_network[0].build_pb_layer()
    for rank in range(1, len(self.client_network)):
      input_shape = self.client_network[rank-1].output_shape
      self.client_network[rank](input_shape = input_shape, rank = rank)
      self.client_network[rank].build_pb_layer()
    

  #记录了数据来源，一开始可能是磁盘，之后可能是HDFS的配置等，做一层封装方便扩展
  #接收一个Dist对象,序列化到self.dist_info
  def set_dist_info(self, dist_info):
    self.dist_info = dist_info
    serialized_dist_info = DistInfo()
    #序列化所有Dist的信息
    serialized_dist_info.data_path = self.dist_info.data_path
    serialized_dist_info.dataset = self.dist_info.dataset
    #信息填充完毕之后放到string 容器中
    string_dist_info = serialized_dist_info.SerializeToString()
    self.dist_info = string_dist_info


  #该函数试图提交计算任务到master但此时还未连接，因此会调用
  #connect_to_master(self)由该函数创建客户端self.task_client并连接
  #连接成功之后发送RPC请求携带序列化对象发送
  #并保存ip，port到属性中，如果断连则可以重连
  def submit(self,ip,port):
    if self.task_client is None:
      self.connect_to_master(ip,port)
    #RPC调用
    self.task_client.submit(self.dist_info, self.network_struct)


  #函数的签名应该要能反映出可以一直调用这个函数
  #但是会得到不同的结果
  #返回值应该是个None类型,因为在函数内如果成功连接则设置了客户端，其他情况均抛出了异常
  #成功情况，第一次调用或只前几次连接都没有成功，这次成功连接上
  #异常情况有以下几种：
  #一、已经调用过建立客户端但是没有连接上，这时候调用该函数就应该跳过建立客户端的部分去完成连接，不发出异常
  #二、已经建立客户端并且已经成功连接，这时候就要抛出一个RepeatedConnectError
  #TODO port异常机制(超出表示范围)
  def connect_to_master(self, ip, port):
    #如果未建立过客户端则建立客户端，否则跳过建立客户端流程
    if self.task_client is None:
      transport = TSocket.TSocket(ip, port)
      transport = TTransport.TBufferedTransport(transport)
      protocol = TBinaryProtocol.TBinaryProtocol(transport)
      #建立客户端
      self.task_client = MLtask.Client(protocol)
    if transport.isOpen():
      raise RepeatedConnectError()
    transport.open()
    logger.info("成功与Master建立连接")

  #该函数每隔固定时间向master请求返回计算结果，若返回不为空则打印
  #若连接失败则重新连接
  def query(self):
    #TODO
    #建立与master连接并接收训练结果机制
