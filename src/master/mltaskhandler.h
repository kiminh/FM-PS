#ifndef MLTASKHANDLER_H
#define MLTASKHANDLER_H

#include<iostream>
#include<vector>

#include<glog/logging.h>

#include"task.h"

#include"../common/transport_info.pb.h"
#include "../common/gen-cpp/MLtask.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

class MLtaskHandler : virtual public MLtaskIf {
 public:
  MLtaskHandler(uint32_t num_workers, uint32_t num_servers)
     : worker_task_is_ready(false),server_task_is_ready(false), num_registed_server_(0), num_registed_worker_(0), 
     current_package_id_(0), num_should_regist_worker_(num_workers), num_should_regist_server_(num_servers) {
      packed_server_tasks_.resize(num_should_regist_server_);
     }

  bool submit(const std::string& dist_info, const std::string& network_struct);

  void query(std::string& _return);

  int32_t worker_regist_to_master();

  void worker_ask_for_task(std::string& _return);

  void worker_submit_kth_result(const std::string& kth_result);

  void server_regist_to_master(const std::string& server_info);

  void server_ask_for_task(std::string& _return);

 private:
  task::DistInfo dist_info_;
  task::NetworkStruct network_struct_;
  Task task_;
  uint32_t num_registed_worker_;
  uint32_t num_registed_server_;
  uint32_t num_should_regist_worker_;
  uint32_t num_should_regist_server_;
  uint32_t current_package_id_;
  //pack parameter
  std::vector<task::ServerTask> packed_server_tasks_;
  bool server_task_is_ready;
  //worker_task会在什么时间准备好呢
  //在所有server节点都注册完毕，并且已经将client提交的任务
  //都打包好之后
  bool worker_task_is_ready;
  //需要有一个vector来保存server信息
  std::vector<task::ServerInfo> info_of_servers_;
  //其实对于所有的worker来说，任务都是一样的，所以可以维护一个对象保存任务
  task::WorkerTask worker_task_;
  void pack_parameters();
  void pack_all_server_tasks();
  void pack_all_worker_tasks();
};

#endif