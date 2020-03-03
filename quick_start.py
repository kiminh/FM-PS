import ...

Model model
model.set_network([
	InputLayer(10, activation = "sigmoid"),
	FClayer(20, activation = "sigmoid"),
	FClayer(10, activation = "softmax")],
	HyperParameter(
		optimizer = "SGD",
		loss = "cross_entropy"
		learning_rate = 0.3,
		epoch = 30,
		mini_batch_size = 15))

model.set_dist_info(Dist("data.zip",  "average","BSP","model_division"))

#根据ip port提交任务到master
master_ip = "127.0.0.3"
master_port = "9696"
model.submit(ip,port)
model.query()

