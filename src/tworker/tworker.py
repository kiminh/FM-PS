import logging

import sys
sys.path.append("../src/exception")

#序列化结构
from common.worker_task_pb2 import *
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
    self.parameter_client = None
    self.server_group = None
    self.task = None
    self.network = None
    self.data = None
    #记录现在训练到第几个epoch
    self.epoch = None
    self.gradient = None
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
    #反序列化任务
    task = self.master_client.worker_ask_for_task().encode()
    logger.info(len(task))
    logger.info(type(task))
    self.task = WorkerTask()
    if not self.task.ParseFromString(task):
      logger.error("反序列化任务失败")
    if self.task.HasField('dataset'):
      logger.info("收到任务中的数据集为"+self.task.dataset)
    if self.task.HasField('data_path'):
      logger.info("收到任务中的数据路径为"+self.task.data_path)

  #加载数据以及动态构建神经网络保存到self.network
  def set_training_env(self):
    pass

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
  def connect_to_server(self):
    pass

  #key operation
  #通过客户端组向server group请求第t轮的参数
  #不同时间返回GradientGroup
  #需要做一个整理到self.parameter
  def pull_parameter(self,t):
    pass

  #将反序列化后的参数更新到self.network
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


