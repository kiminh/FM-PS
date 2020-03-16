#include"mltaskhandler.h"

#include<random>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

bool MLtaskHandler::submit(const std::string& dist_info, const std::string& network_struct){
  //承接receive_task任务
  bool deserialize_dist_info_success = dist_info_.ParseFromString(dist_info);
  bool deserialize_network_struct = network_struct_.ParseFromString(network_struct);
  if(! deserialize_dist_info_success || !deserialize_network_struct){
    LOG(INFO) << "反序列化分布式信息" << deserialize_dist_info_success;
    LOG(INFO) << "反序列化网络结构" << deserialize_network_struct;
    return false;
  }
  pack_all_worker_tasks();
  pack_all_server_tasks();
  return true;
}

int32_t MLtaskHandler::worker_regist_to_master() {
  LOG(INFO) << "worker注册中";
  int32_t id = num_registed_worker_++;
  LOG(INFO) << "当前id" << id;
  return id;
}

void MLtaskHandler::worker_ask_for_task(std::string& _return) {
  if(!worker_task_is_ready){
    return;
  }
  //序列化为字符串
  string serialized_task;
  if(!worker_task_.SerializeToString(&serialized_task)){
    LOG(INFO) << "序列化worker任务失败";
  }
  LOG(INFO) << "任务字节数：" << serialized_task.length();
  //返回
  _return = serialized_task;
}

void MLtaskHandler::server_ask_for_task(std::string& _return) {
  //TODO:
  //check task is ready or not
  if(!server_task_is_ready){
    //LOG(INFO) << "任务尚未打包完成";
    return;
  }
  if(current_package_id_ >= num_should_regist_server_){
    LOG(INFO) << "领取次数超出范围(一个server一轮只允许一次)";
    LOG(INFO) << "已领取次数："  << current_package_id_;
    return;
  }
  //序列化当前任务
  string current_task;
  packed_server_tasks_[current_package_id_].SerializeToString(&current_task);
  current_package_id_++;
  LOG(INFO) << "任务长度:" << current_task.length();
  _return = current_task;
}

//TODO网络结构可能会更改为图
void MLtaskHandler::pack_parameters(){
  //对于每层网络
  //修改参数分配机制由hash改为随机数分配
  //hash 到 某一server
  //问题hash的并不均匀，很难hash到0
  default_random_engine random;
  uniform_int_distribution<size_t> range(0, num_should_regist_server_-1);
  //Input层需要去除
  for(int i = 1; i < network_struct_.layers_size(); i++){
    const task::Layer& layer = network_struct_.layers(i);
    //修改参数分配机制由hash改为随机数分配
    //每一个参数
    for(int j = 0; j < layer.parameter_list_size(); j++){
      const task::Parameter& parameter = layer.parameter_list(j);
      //无非就是一个随机数问题，只要对于这个key产生一个0-num_should_regist_server_-1的随机数
      //size_t target = hash_str_to_long(parameter.key().c_str()) % num_should_regist_server_;
      size_t target = range(random);
      auto current_parameter = packed_server_tasks_[target].add_parameter_list();
      LOG(INFO) << "dispatch parameter: " << parameter.key() << " to " << target;
      //set key
      current_parameter->set_key(parameter.key());
      //set shape
      for(int k = 0; k < parameter.shape_size(); k++){
        current_parameter->add_shape(parameter.shape(k));
      }
      //set dim
      current_parameter->set_dim(parameter.dim());
    }
  }
  LOG(INFO) << "参数打包完毕";
}

void MLtaskHandler::pack_all_server_tasks(){
  pack_parameters();
  uint32_t epoch = network_struct_.hparameter().epoch();
  string optimizer(network_struct_.hparameter().optimizer()); 
  float learning_rate = network_struct_.hparameter().learning_rate();
  for(auto server_task : packed_server_tasks_){
    server_task.set_epoch(epoch);
    server_task.set_optimizer(optimizer);
    server_task.set_learning_rate(learning_rate);
  }
  LOG(INFO) << "server任务成功打包为" << packed_server_tasks_.size() << "包";
  server_task_is_ready = true;
}

//TODO
void MLtaskHandler::query(std::string& _return) {
  // Your implementation goes here
  printf("query\n");
}

//TODO
void MLtaskHandler::worker_submit_kth_result(const std::string& kth_result) {
  // Your implementation goes here
  printf("worker_submit_kth_result\n");
}

void MLtaskHandler::server_regist_to_master(const std::string& server_info) {
  //增加注册服务器数量并反序列化注册信息保存起来
  num_registed_server_++;
  task::ServerInfo current_info;
  current_info.ParseFromString(server_info);
  LOG(INFO) << current_info.ip() << " " << current_info.port() << " 已注册";
  info_of_servers_.push_back(current_info);
  LOG(INFO) << "记载了" << info_of_servers_.size() << "server节点信息" << endl; 
}

void MLtaskHandler::pack_all_worker_tasks(){
  //数据信息
  //data_path
  worker_task_.set_data_path(dist_info_.data_path());
  //data_division
  worker_task_.set_data_division(dist_info_.data_division());
  //data_set
  worker_task_.set_dataset(dist_info_.dataset());
  //TODO
  //网络信息
  //通信信息
  //ServerInfo
  if(num_registed_server_ != num_should_regist_server_){
    LOG(ERROR) << "在打包Pserver节点时发现节点注册数量出现错误";
    LOG(INFO) << "应注册节点:" << num_should_regist_server_;
    LOG(INFO) << "实际注册节点:" << num_registed_server_;
    return;
  }
  //打包节点信息
  const size_t size = info_of_servers_.size();
  for(size_t i = 0; i < size; i++){
    auto server_info = worker_task_.add_servers();
    server_info->set_ip(info_of_servers_[i].ip());
    server_info->set_port(info_of_servers_[i].port());
  }
  worker_task_is_ready = true;
  LOG(INFO) << "Tworker任务打包完毕";
}