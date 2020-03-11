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
     : num_registed_worker_(0), num_should_regist_worker_(num_workers), num_should_regist_server_(num_servers) {
      packed_server_tasks_.resize(num_should_regist_server_);
     }

  bool submit(const std::string& dist_info, const std::string& network_struct);

  void query(std::string& _return);

  void worker_regist_to_master(std::string& _return, const std::string& worker_info);

  void worker_ask_for_task(std::string& _return);

  void worker_submit_kth_result(const std::string& kth_result);

  void server_regist_to_master(std::string& _return, const std::string& server_info);

  void server_ask_for_task(std::string& _return);

 private:
  task::DistInfo dist_info_;
  task::NetworkStruct network_struct_;
  Task task_;
  uint32_t num_registed_worker_;
  uint32_t num_should_regist_worker_;
  uint32_t num_should_regist_server_;
  uint32_t current_package_id;
  //pack parameter
  std::vector<task::ServerTask> packed_server_tasks_;
  bool server_task_is_ready;
  void pack_parameters();
  void pack_all_server_tasks();
};

#endif