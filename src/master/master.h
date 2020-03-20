#ifndef MASTER_H
#define MASTER_H

#include<vector>
#include<string>
#include<memory>

#include"../common/nodeinfo.h"

#include"mltaskhandler.h"

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>


//构造函数：
//Master(int port){}
//@para int port
//根据合法的端口用thrift来建立一个服务器对象TSimpleserver task_server_
class Master{
 public:
  //构造
  Master(int port, uint32_t num_workers, uint32_t num_servers);

  void start_serve();

  //关闭整个集群
  void shut_down_cluster();

 private:
  int port_;
  uint32_t num_workers_;
  uint32_t num_servers_;
  std::shared_ptr<::apache::thrift::server::TThreadPoolServer> task_server_;
};
#endif
