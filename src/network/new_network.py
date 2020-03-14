# -*- coding:utf-8 -*-

import layer
import numpy as np

class Network(object):
	def __init__(self,layers,calculate = 'numpy'):
		self.layers = layers
		#设定计算选定(numpy,my_python,my_c++)
		for layer in range(1,len(self.layers)):
			self.layers[layer].calculate = calculate
		self.loss = None

	def training(self, x_train, y_train, x_test, y_test, epochs, learning_rate,mini_batch_size):
		num_data = len(x_train)
		for i in range(epochs):
			pack = list(zip(x_train,y_train))
			batches = [pack[j:j+mini_batch_size] for j in range(0,num_data,mini_batch_size)]
			#x是(784,)向量，y是(10,)向量
			for mini_batch in batches:
				self.update(mini_batch,learning_rate)

			print("Epochs:{0}".format(i+1), end = '    ')
			self.evaluate(x_test,y_test)

	def update(self,mini_batch,learning_rate):
		#计算累计怎么更新权重
		for x,t in mini_batch:
			#除最后一层
			y = self.feedforward(x)
			#最后一层
			self.layers[-1](y,input_size = y.shape[0],t = t)
			#backward
			self.backward()
		self.optimizer(learning_rate,len(mini_batch))

	def backward(self):
		value = self.loss
		for i in range(-1,-len(self.layers),-1):
			value = self.layers[i].backward(value)
		return value

	def sgd(self,learning_rate,size):
		for l in range(-1,-len(self.layers),-1):
			self.layers[l].w = self.layers[l].w - learning_rate * self.layers[l].one_batch_dw / size
			self.layers[l].b = self.layers[l].b - learning_rate * self.layers[l].one_batch_db / size
			
	def optimizer(self,learning_rate,num):
		self.sgd(learning_rate,num)
		#更新后清空累计的dw
		for l in range(-1,-len(self.layers),-1):
			self.layers[l].one_batch_dw = 0
			self.layers[l].one_batch_db = 0

	def evaluate(self,x_test, y_test):
		list = [np.argmax(self.predict(x)) for x,y in zip(x_test,y_test) if np.argmax(self.predict(x)) == y]
		print(list[0:10])
		count = sum([1 for x,y in zip(x_test,y_test) if np.argmax(self.predict(x)) == y])
		accuracy = (count / len(y_test))*100
		print(count, " / ", len(y_test), "   ", accuracy)
		
		
	def feedforward(self,x):
		y = x
		size = self.layers[0].input_size[0]
		for l in range(1,len(self.layers)-1):
			y = self.layers[l](y,input_size = size)
			size = self.layers[l].output_size
		return y

	def predict(self,x):
		y = x
		size = self.layers[0].input_size[0]
		for l in range(1,len(self.layers)):
			y = self.layers[l](y,input_size = size)
			size = self.layers[l].output_size
		return y