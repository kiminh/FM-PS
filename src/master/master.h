#ifndef MASTER_H
#define MASTER_H

#include<vector>
#include<string>

//#include"../common/transport.pb.h"
#include"../common/nodeinfo.h"
#include"../common/dist_info.pb.h"
#include"../common/network_struct.pb.h"
#include"../common/worker_task.pb.h"

#include"task.h"

//server.cpp
#include "../common/gen-cpp/MLtask.h"
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>


//构造函数：
//Master(int port){}
//@para int port
//根据合法的端口用thrift来建立一个服务器对象TSimpleserver task_server_


//void recive_task(NetworkStruct&, DistInfo&);
//@para 序列化网络结构
//@para 序列化分布式信息
//在由model请求的rpc提交任务的submit中的子函数
//构造一个Task对象保存训练任务

//void count_kth_result(TaskResult&);
//@para worker向master请求提交暂时结果的引用
//return 无
//功能：将序列化后的训练结果反序列化并且汇总到std::vector<KthResult>的第k个元素

//int handle_worker_regist(std::string ip, int port);
//@para worker ip
//@para worker port
//return worker id
//在注册请求中接收worker信息,创建NodeInfo添加到connected_worker中返回id


//bool check_ready_to_dispatch_task();
//@para 无
//return 返回是否可以分配任务给worker/server
//worker/server通过loop请求计算任务，master在确认所有worker和server均连接之后，并且计算任务已经完整保存到Task之后，此时可以分配

//WorkerTask pack_worker_task();
//@para 无
//return 返回worker的计算任务以及需要连接的server对象的信息
//在任务和注册均完成之后，若此时收到worker_ask_for_task()的请求,则从Task和std::vector<NodeInfo> server_
//中解析并打包成WorkerTask(序列化对象)

//ServerTask pack_server_task();
//@para 无
//return 返回server所需要的计算任务ServerTask

class Master{
 public:
  //构造
  Master(int port) : port_(port){}

  void start_serve();

  //worker注册函数
  int handle_worker_regist(std::string ip, int port);

  //server注册函数
  int handle_server_regist(std::string ip, int port);

  //检查是否可以进行分配任务的函数
  bool check_ready_to_dispatch_task();

  //打包worker计算任务
  //task::WorkerTask pack_worker_task();

  //打包server计算任务
  //task::ServerTask pack_server_task();

  //将第k轮结果发送给Model
  //void count_kth_result(task::KthResult&);

  //关闭整个集群
  void shut_down_cluster();

 private:
  int port_;
  apache::thrift::server::TSimpleServer* task_server_;
  std::vector<NodeInfo> connected_server_;
  //std::vector<task::KthResult> kth_result_;
};
#endif
