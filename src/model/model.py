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
