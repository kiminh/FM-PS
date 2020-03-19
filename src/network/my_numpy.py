import numpy as np
import my_c_matrix as mcm

def	zeros(row,column):
	return [[0 for i in range(column)] for j in range(row)]

def dot(x,y,calculate = 'numpy'):
	if calculate == 'numpy':
		return np.dot(x,y)
	elif calculate == 'my_python':
		#处理行向量
		if isinstance(x,np.ndarray):
			if x.ndim == 1:
				x = x.reshape(1,x.shape[0])
		elif isinstance(x,list):
			if not isinstance(x[0],list):
				x = [x]
		x_row = len(x)
		x_column = len(x[0])
		y_row = len(y)
		y_column = len(y[0])
		if(x_column != y_row):
			print("size doesn't match")
			return None
		result = zeros(x_row,y_column)
		for i in range(x_row):
			for j in range(y_column):
				for k in range(y_row):
					result[i][j] += x[i][k] * y[k][j]
		if(x_row == 1):
			return np.array(result).reshape((y_column,))
		return np.array(result)
	elif calculate == 'my_c++':
		if isinstance(x,np.ndarray):
			if x.ndim == 1:
				x = x.reshape(1,x.shape[0])
				x = list(x)
		elif isinstance(x,list):
			if not isinstance(x[0],list):
				x = [x]
		result = mcm.dot(x,y)
		if(len(result) == 1 and isinstance(result[0],list)):
			result = result[0]
		return np.array(result)
		
		
		
		