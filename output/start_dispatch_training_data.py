import sys
sys.path.append("../src/client_model")

from model import Model
from dist_info import Dist

client = Model()
client.set_dist_info(Dist(data_path = "../../data/mnist.pkl.gz", dataset = "MNIST"))

master_ip = "10.0.0.15"
master_port = "1000"

client.submit(master_ip,master_port)
print("提交")
client.query()