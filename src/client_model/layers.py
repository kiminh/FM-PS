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

#参数key""
class FClayer(Layer):
  def __init__(self, input_size, activation):
    self.size = input_size
    self.activation = activation
    self.name = "dense"
    self.name_w = self.name + "_w"
    self.name_b = self.name + "_b"
  def serialize(self):
    pass