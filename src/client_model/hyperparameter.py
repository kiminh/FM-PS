class ClientHyperParameter(object):
  def __init__(self, optimizer, learning_rate, epoch, mini_batch_size, loss):
    self.optimizer = optimizer
    self.learning_rate = learning_rate
    self.epoch = epoch
    self.mini_batch_size = mini_batch_size
    self.loss = loss