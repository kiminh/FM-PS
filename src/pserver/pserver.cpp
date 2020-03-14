#include"pserver.h"
#include<sys/socket.h>

#include<glog/logging.h>

#include<cstdio>


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace ::apache::thrift::concurrency;

Pserver::Pserver(const std::string& master_ip, int master_port, int parameter_server_port)
  : master_ip_(master_ip),
  master_port_(master_port), parameter_server_port_(parameter_server_port){}


//该参数服务器一定要是多线程的
//因此选择thrift TThreadPollServer
//主线程负责监听
//异常分析，如果建立失败则需要抛出异常给main处理
void Pserver::build_parameter_server(){
  handler_ = make_shared<ParameterServerHandler>();
  shared_ptr<TProcessor> processor(make_shared<ParameterServerProcessor>(handler_));
  shared_ptr<TServerTransport> server_transport(make_shared<TServerSocket>(parameter_server_port_));
  shared_ptr<TTransportFactory> transport_factory(make_shared<TBufferedTransportFactory>());
  shared_ptr<TProtocolFactory> protocol_factory(make_shared<TBinaryProtocolFactory>());
  //TODO
  //不要写magic number统一放在一个头文件
  const int num_threads = 4;
  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(num_threads);
  shared_ptr<ThreadFactory> threadFactory = shared_ptr<ThreadFactory>(new ThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  parameter_server_ = make_shared<TThreadPoolServer>(processor, server_transport, transport_factory, protocol_factory, threadManager);
  LOG(INFO) << "参数服务器建立,但未开始服务";
  //TODO:怎么检测建立失败的异常抛给main
}

//建立客户端是一次性的所以先需要判断是否已经存在客户端
//若存在则不需要再建立一次，但有可能连接失败或未连接
void Pserver::build_client_and_connect_to_master(){
  if(!task_){
    LOG(INFO) << "注册的master_ip" << master_ip_;
    LOG(INFO) << "注册的master_port" << master_port_;
    shared_ptr<TTransport> socket(new TSocket(master_ip_, master_port_));
    transport_ = make_shared<TBufferedTransport>(socket);
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport_));
    task_ = make_shared<MLtaskClient>(protocol);
    MLtaskClient task(protocol);
  }
  if(transport_->isOpen()){
    return;
  }
  transport_->open();
}


//注册到master
bool Pserver::regist_to_master(){
  //确保
  if(!transport_ || !transport_->isOpen()){
    LOG(ERROR) << "注册时并未建立与master连接";
    return false;
  }
  //打包本进程ip port
  task::ServerInfo my_info;
  my_info.set_ip(get_ip());
  my_info.set_port(parameter_server_port_);
  string info;
  my_info.SerializeToString(&info);
  task_->server_regist_to_master(info);
  return true;
}

string Pserver::get_ip(){
  string ip;
  ostringstream oss_cmd;
  oss_cmd << "ip route get 1 | awk '{print $7; exit}'";
  FILE* f_command = popen(oss_cmd.str().c_str(), "r");
  if(f_command){
    char buffer[1024];
    if(!fgets(buffer, sizeof(buffer)-1, f_command)){
      LOG(ERROR) << "读取ip 错误";
    }
    pclose(f_command);
    ip = buffer;
  }
  return ip;
}

void Pserver::ask_for_task(){
  string server_task;
  //loop 请求非空任务
  while(true){
    //过于频繁导致提交的任务得不到响应
    (*task_).server_ask_for_task(server_task);
    if(!server_task.empty()){
      server_task_.ParseFromString(server_task);
      break;
    }
  }
  //打印信息
  /*
  for(int i = 0; i < server_task_.parameter_list_size(); i++){
    const task::Parameter& parameter = server_task_.parameter_list(i);
    LOG(INFO) << parameter.key();
    for(int j = 0; j < parameter.shape_size(); j++){
      LOG(INFO) << parameter.shape(j) << " ";
    }
  }*/
}

//对于每一个参数构建一个对象（vector 或者矩阵）
//进行初始化，建立这个映射
void Pserver::load_parameter_to_memory(){
  //TODO,目前默认初始化为随机初始化
  float upper_bound = 1.0;
  float lower_bound = 0.0;
  for(int i = 0; i < server_task_.parameter_list_size(); i++){
    const task::Parameter& parameter = server_task_.parameter_list(i);
    //根据dim判断类型
    //随机赋值后加入哈希表
    if(1 == parameter.dim()){
      /*
      shared_ptr<VectorParameter> value 
          = make_shared<VectorParameter>(parameter.data_type(), {parameter.shape(0)});
      value->set_random(upper_bound, lower_bound);*/
      VectorParameter* value = new VectorParameter(1, {parameter.shape(0)});
      //shared_ptr<VectorParameter> value = make_shared<VectorParameter>(1, {parameter.shape(0)});
      value->set_random(upper_bound, lower_bound);
      parameter_[parameter.key()] = value;
    }
    else if(2 == parameter.dim()){
      /*shared_ptr<MatrixParameter> value 
        = make_shared<MatrixParameter>(1, {parameter.shape(0), parameter.shape(1)});*/
      MatrixParameter* value = new MatrixParameter(1, {parameter.shape(0), parameter.shape(1)});
      value->set_random(upper_bound,lower_bound);
      parameter_[parameter.key()] = value;
    }
  }
}

void Pserver::load_all_tasks_to_handler(){
;
}

void Pserver::print_in_memory_parameter(){
  for(auto iterator = parameter_.begin(); iterator != parameter_.end(); iterator++){
    LOG(INFO) << (*iterator).first;
    ParameterValue* value = (*iterator).second;
    const int dim = value->shape_.size();
    LOG(INFO) << "是" << dim << "维的参数";
    LOG(INFO) << "值为:";
    value->print_value();
  }
  
}