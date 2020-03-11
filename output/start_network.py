import sys
sys.path.append("../src/client_model")
sys.path.append("../src/common/")

from model import Model
from dist_info import *
from client_layers import *
from hyperparameter import *


client = Model()
client.set_network([
  InputLayer(784),
  DenseLayer(30, "sigmoid"),
  DenseLayer(15, "sigmoid"),
  DenseLayer(20, "sigmoid")],
  ClientHyperParameter(
  optimizer = "SGD",
  loss = "cross_entropy",
  learning_rate = 0.3,
  epoch = 30,
  mini_batch_size = 15)
)

client.set_dist_info(Dist(data_path = "../../data/mnist.pkl.gz", dataset = "MNIST"))

master_ip = "10.0.0.15"
master_port = "1000"

client.submit(master_ip,master_port)
print("提交")
client.query()
