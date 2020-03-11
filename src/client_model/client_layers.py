from transport_info_pb2 import *

class BaseLayer(object):
  def __init__(self,output_shape):
    self.output_shape = output_shape

class InputLayer(BaseLayer):
  def __init__(self, data_shape):
    #根据输入数据的shape的形状，类型来确定dim,以及shape
    #可能是一个list
    self.data_shape = data_shape
    self.output_shape = data_shape
    #每一层都应该有一个名字
    self.name = "Input"
    self.pb_layer = None

  #worker需要知道输入层的形状就可以了
  #而server不需要知道输入层的信息
  #因此仍然需要管理一个序列化对象
  def build_pb_layer(self):
    self.pb_layer = Layer()
    self.pb_layer.name = self.name
    parameter = self.pb_layer.parameter_list.add()
    parameter.key = self.name+"_"+"datashape"
    #暂且定为一个int
    parameter.shape.append(self.data_shape)

class DenseLayer(BaseLayer):
  def __init__(self, output_shape, activation):
    self.output_shape = output_shape
    self.activation = activation
    #在model call 时确定
    self.input_shape = None
    self.name = "Dense"
    #是第几层的网络，worker需要知道以此来构造
    #同样由model call时确定
    self.rank = None
    #参数名称(for hash)作为key-value的key
    self.name_w = self.name + "_w"
    self.name_b = self.name + "_b"
    #最重要的要知道w，b的shape在call的时候确定
    self.w_shape = None
    self.b_shape = None
    #同样需要维护pb_layer对象，并完成序列化
    self.pb_layer = None

  #需要model进行call 才能确定参数的shape
  def __call__(self, input_shape = None, rank = None):
    self.input_shape = input_shape
    #先暂定为二维的矩阵
    #一个元组
    self.w_shape = (self.input_shape, self.output_shape)
    self.b_shape = (self.input_shape, self.output_shape)
    self.rank = rank
    self.name_w = self.name_w + "_" + str(self.rank)
    self.name_b = self.name_b + "_" + str(self.rank)
  
  def build_pb_layer(self):
    self.pb_layer = Layer()
    self.pb_layer.name = self.name
    self.pb_layer.activation = self.activation
    w = self.pb_layer.parameter_list.add()
    w.key = self.name_w
    w.shape.append(self.w_shape[0])
    w.shape.append(self.w_shape[1])
    b = self.pb_layer.parameter_list.add()
    b.key = self.name_b
    b.shape.append(self.b_shape[0])
    b.shape.append(self.b_shape[1])

#TODO:加入更多种类的神经网络层