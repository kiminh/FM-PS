import gzip
import pickle
import numpy as np
import logging

logging.basicConfig(level=logging.INFO,
              format='%(asctime)s %(levelname)s '
              '%(filename)s:%(lineno)d; '
              '%(message)s')
logger = logging.getLogger(__name__)

class FileHandler(object):
  def __init__(self,path, dataset):
    self.path = path
    self.dataset = dataset
  def open(self):
    pass

class DiskFileHandler(FileHandler):
  def __init__(self,path, dataset):
    self.path = path
    self.dataset = dataset
    self.file = None
  
  def open(self):
    if "MNIST" == self.dataset:
      self.file = gzip.open(self.path, "rb")
      return self.file



class DataLoader(object):
  def __init__(self, path, division = None, id = None, host = None, port = None, dataset = None):
    self.path = path
    self.division = division
    self.id = id
    self.address = (host, port)
    self.dataset = dataset
  
    #返回不同存储介质的访问类
  def get_file_handler(self):
    store_env = self.path.split("://")[0]
    logger.info("存储环境为"+store_env)
    #hdfs
    if "hdfs" == store_env:
      pass
    #disk
    else:
      logger.info("对"+self.path+"的"+self.dataset+"数据集进行加载")
      return DiskFileHandler(self.path, self.dataset)


  #返回可训练的数据
  def get_data(self):
    #根据path创建不同的存储介质处理
    handler = self.get_file_handler()
    file = handler.open()
    if("MNIST" == self.dataset):
      training, validation, test = pickle.load(file,encoding='unicode-escape')
      logger.info("training:" + len(training)+" validation:"+len(validation)+" test:"len(test))
      return (training,validation,test)
  
