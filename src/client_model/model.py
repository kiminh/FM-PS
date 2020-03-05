import logging

import sys
sys.path.append("../src/common")
sys.path.append("../src/common/gen-py")

from dist_info_pb2 import *
from task import MLtask
from task.ttypes import *
from task.constants import *
 
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

logging.basicConfig(level = logging.INFO)
logger = logging.getLogger(__name__)

class Model(object):
  def __init__(self):
    #此为序列化后对象
    self.network_struct = None
    self.dist_info = None
    #Model内需要封装一个客户端，向Master提交任务并且接收计算结果
    self.task_client = None

  #接收一个网络结构列表，逐层解析出网络结构信息，序列化到self.network_struct
  #self.network_struct是一个protobuf的序列化对象
  def set_network(self, network, hyperparameter):
    pass

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
    if self.task_client is not None:
      self.connect_to_master(ip,port)
    #数据任务task
    #TODO,目前只有训练数据信息 
    task = self.dist_info.decode('utf-8')
    #RPC调用
    self.task_client.submit(task)


  #创建客户端并到master
  #若成功连接则打印信息退出，不成功则由用户选择是否再次连接
  def connect_to_master(self, ip, port):
    try:
      transport = TSocket.TSocket(ip, port)
      transport = TTransport.TBufferedTransport(transport)
      protocol = TBinaryProtocol.TBinaryProtocol(transport)
      #建立客户端
      self.task_client = MLtask.Client(protocol)
      transport.open()
      logger.info("成功与"+ip+" "+str(port)+建立客户端")
    except Thrift.TException as tx:
      logger.error(tx.message)

  #该函数每隔固定时间向master请求返回计算结果，若返回不为空则打印
  #若连接失败则重新连接
  def query(self):
    pass
