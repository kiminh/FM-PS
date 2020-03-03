#worker建立之初,可以通过main函数告诉该类master的ip和port

#Tworker职责在于拉取最新的参数，算出本轮梯度push到服务端
class Tworker(object):
	del __init__(self,master_ip,master_port):
		self.master_ip = master_ip
		self.master_port = master_port
		self.id = None
		#与master的客户端
		self.master_client = None
		#与一组server的客户端列表
		self.parameter_client = None
		self.server_group = None
		self.task = None
		self.network = None
		self.data = None
		#记录现在训练到第几个epoch
		self.epoch = None
		self.gradient = None

#query_task

	#根据全局Master信息建立客户端self.master_client
	#@para无
	#序列化为SerializedNodeInfo，并向master提出注册请求
	#return bool值标志是否注册成功
	#调用注册rpc服务会返回一个id需要保存到self.id
	def build_client_to_master(self):
		pass

	#@para无
	#return 任务信息WorkerTask（内含一组需要连接的服务器）
	#需要保存到self.task以及self.server_group
	def ask_for_task(self):
		pass

	#根据self.task中各层的信息和优化器等信息
	#加载数据以及动态构建神经网络保存到self.network
	def set_training_env(self):
		pass

	#根据self.task中的数据路径
	#以及任务划分模式
	#"average" = id * data_size / work_nums (可以算出起始位置)
	#有了路径，有了如何分配那么就可以把数据加载到self.data
	#同时根据路径不同文件格式解析训练数据
	def load_data(self):
		pass

	#根据self.server_group中的信息建立一个客户端组
	def connect_to_server(self):
		pass

	#key operation
	#通过客户端组向server group请求第t轮的参数
	#不同时间返回GradientGroup
	#需要做一个整理到self.parameter
	def pull_parameter(self,t):
		pass

	#将反序列化后的参数更新到self.network
	def fill_newest_parameter(self):
		pass

	#开始第t个epoch的训练
	#首先拉取参数，之后更新现有网络的参数，然后开始训练
	#保存第t轮的梯度到self.gradient
	def train(self,t):
		pass

	#将梯度根据self.server_group中的id进行分片
	#返回分组完成的梯度列表
	def slice_gradient():
		pass

	#key operation
	#通过slice_gradient完成的列表，客户端组发送梯度到连接的服务端
	def push_gradient(self):
		pass

	#将第t轮的forward结果传给master
	def evaluation(self,t):
		pass	


