class Layer(object):
  def __init__(self, input_size, activation):
    self.size = input_size
    self.activation = activation

#参数key为"input_w", "input_b"
class InputLayer(Layer):
  def __init__(self, input_size, activation):
    self.size = input_size
    self.activation = activation
    self.name = "input"
    self.name_b = self.name + "_b"
  def serialize(self):
    pass

#参数key为""
class FClayer(Layer):
  def __init__(self, input_size, activation):
    self.size = input_size
    self.activation = activation
    self.name = "dense"
    self.name_w = self.name + "_w"
    self.name_b = self.name + "_b"
  def serialize(self):
    pass
  

class HyperParameter(object):
  def __init__(self, optimizer, learning_rate, epoch, mini_batch_size)
    self.optimizer = optimizer
    self.learning_rate = learning_rate
    self.epoch = epoch
    self.mini_batch_size = mini_batch_size

class Dist(object):
  def __init__(self, data_path, data_division, consistence, model_division):
    self.data_path = data_path
    self.data_division = division
    self.consistence = consistence
    self.model_division = model_division

class Model(object):
  del __init__(self):
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
    pass

  #该函数试图提交计算任务到master但此时还未连接，因此会调用
  #connect_to_master(self)由该函数创建客户端self.task_client并连接
  #连接成功之后发送RPC请求携带序列化对象发送
  #并保存ip，port到属性中，如果断连则可以重连
  def submit(self,ip,port):
    pass

  #创建客户端并到master
  #若成功连接则打印信息退出，不成功则由用户选择是否再次连接
  def connect_to_master(self)
    pass

  #该函数每隔固定时间向master请求返回计算结果，若返回不为空则打印
  #若连接失败则重新连接
  def query(self):
    pass
