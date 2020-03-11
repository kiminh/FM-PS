from client_layers import *
network = [
  InputLayer(784),
  DenseLayer(30, "sigmoid"),
  DenseLayer(15, "sigmoid"),
  DenseLayer(20, "sigmoid")]