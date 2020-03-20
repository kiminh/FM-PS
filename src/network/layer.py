import numpy as np
import my_numpy as mnp

class BaseLayer(object):
  def __init__(self,input_size = None):
    self.input_size = input_size

class InputLayer(BaseLayer):
  def __init__(self,input_size):
    BaseLayer.__init__(self,input_size)
    self.data = None

class FullConnected(BaseLayer):
  def __init__(self,output_size,activation,input_size = None):
    BaseLayer.__init__(self,input_size)
    self.built = None
    self.output_size = output_size
    self.activation = activation
    self.one_batch_dw = 0
    self.one_batch_db = 0
    self.calculate = None
    #分布式机器学习参数
    self.w_name = None
    self.b_name = None
    self.w = None
    self.b = None

  #需要从外部fill参数到层内
  #通过parameter指定是什么参数
  def fill_parameters(self, values, parameter, key = None):
    if parameter == 'w':
      self.w = values
      #print(self.w)
      if self.w_name is None:
        self.w_name = key
    elif parameter == 'b':
      self.b = values
      #print(self.w)
      if self.b_name is None:
        self.b_name = key
    if self.w is not None and self.b is not None:
      self.built = True

  def __call__(self, x, input_size = None, t = None):
    if self.built is None:
      self.w = np.random.randn(input_size,self.output_size)
      self.b = np.random.randn(self.output_size)
      self.built = True
    self.x = x
    if(t is not None):
      return self.activation(mnp.dot(x,self.w,self.calculate) + self.b, t)
    return self.activation(mnp.dot(x,self.w,self.calculate) + self.b)

  def backward(self,y):
    y = self.activation.backward(y)
    trans = self.x.reshape(self.x.shape[0],1)
    #print(self.w_name)
    #print(y)
    self.dw = mnp.dot(trans,y.reshape(1,y.shape[0]),self.calculate)
    self.db = y
    self.one_batch_dw += self.dw
    self.one_batch_db += self.db
    self.dx = mnp.dot(y,self.w.transpose(),self.calculate)
    return self.dx

class Sigmoid(BaseLayer):
  def __init__(self,input_size = None):
    BaseLayer.__init__(self,input_size)

  def __call__(self,x):
    self.x = x
    #print(x)
    self.y = self.sigmoid(x)
    return self.y

  def backward(self,value):
    self.dx = value * self.y * (1 - self.y)
    return self.dx

  def sigmoid(self,x):
    #return 1.0/(1.0 + np.exp(-x))
    return .5 * (1 + np.tanh(.5 * x))

class SoftmaxLoss(BaseLayer):
  def __init__(self,input_size = None):
    BaseLayer.__init__(self,input_size)
    self.loss = None
  
  def __call__(self,x,t = None):
    self.x = x
    self.y = self.softmax(x)
    self.t = t
    if(t is not None):
      self.loss = self.crossentropy(self.y,self.t)
    return self.y

  def backward(self,value):
    self.dx = self.y - self.t
    return self.dx

  def softmax(self,x):
    x = x - np.max(x)
    return np.exp(x) / np.sum(np.exp(x))

  def crossentropy(self,y,t):
    delta = 1e-7
    return -np.sum(t * np.log(y+delta))

