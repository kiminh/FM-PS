#include"mltaskhandler.h"

#include<functional>

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
  task_.dataset = dist_info_.dataset();
  task_.data_path = dist_info_.data_path();
  pack_all_server_tasks();
  return true;
}

void MLtaskHandler::worker_regist_to_master(std::string& _return, const std::string& worker_info) {
  //TODO更改接口应该为uint
  string id = to_string(num_registed_worker_++);
  _return = id;
}

void MLtaskHandler::worker_ask_for_task(std::string& _return) {
  //TODO增加任务check逻辑
  //Task 信息序列化到WorkerTask(protobuf对象)
  task::WorkerTask worker_task;
  worker_task.set_data_path(task_.data_path);
  worker_task.set_dataset(task_.dataset);
  LOG(INFO) << worker_task.data_path();
  LOG(INFO) << worker_task.dataset();
  //序列化为字符串
  string serialized_task;
  if(!worker_task.SerializeToString(&serialized_task)){
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
    LOG(INFO) << "任务尚未打包完成";
    return;
  }
  if(current_package_id >= num_should_regist_server_){
    LOG(INFO) << "领取次数超出范围(一个server一轮只允许一次)";
    LOG(INFO) << "已领取次数："  << current_package_id;
    return;
  }
  //序列化当前任务
  string current_task;
  packed_server_tasks_[current_package_id].SerializeToString(&current_task);
  current_package_id++;
  LOG(INFO) << "任务长度:" << current_task.length();
  _return = current_task;
}

//TODO网络结构可能会更改为图
void MLtaskHandler::pack_parameters(){
  //对于每层网络
  for(int i = 0; i < network_struct_.layers_size(); i++){
    const task::Layer& layer = network_struct_.layers(i);
    //每一个参数
    for(int j = 0; j < layer.parameter_list_size(); j++){
      const task::Parameter& parameter = layer.parameter_list(j);
      //hash 到 某一server
      size_t target = hash(parameter.key()) % num_should_regist_server_;
      auto current_parameter = packed_server_tasks_[target].add_parameter_list();
      //set key
      current_parameter->set_key(parameter.key());
      //set shape
      for(int k = 0; k < parameter.shape_size(); k++){
        current_parameter->add_shape(parameter.shape(k));
      }
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

//TODO
void MLtaskHandler::server_regist_to_master(std::string& _return, const std::string& server_info) {
  // Your implementation goes here
  printf("server_regist_to_master\n");
}