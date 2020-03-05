from data_handler import *

data_loader = DataLoader(path = "./data/mnist.pkl.gz", dataset = "MNIST")
data = data_loader.get_data()