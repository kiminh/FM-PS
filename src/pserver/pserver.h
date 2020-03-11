#ifndef PSERVER_H
#define PSERVER_H

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/server/TThreadPoolServer.h>

#include<string>
#include<unordered_map>

#include"../common/gen-cpp/MLtask.h"

#include"../common/transport_info.pb.h"
#include"../common/nodeinfo.h"

#include"parametervalue.h"

#include"parameter_server_handler.h"

class Pserver{
 public:
  //构造
  Pserver(const std::string& master_ip, int master_port, int parameter_server_port);
  
  //调用建立参数服务器的user是main，因此如果建立不成功就要抛出异常给它
  //成功的话只是把参数服务器建立起来，不需要返回什么信息给它
  void build_parameter_server();

  void build_client_and_connect_to_master();

  //如果注册失败则返回失败否则注册成功
  bool regist_to_master();

  //loop请求master响应任务
  //并将返回的信息存入ServerTask
  void ask_for_task();

  //根据SeverTask中的信息加载对应参数到parameter_
  void load_parameter_to_memory();

  //异步
  //异步就是每在push请求中收到一组梯度就更新对应梯度
  void update_parameter();
  
  //检查第t轮的参数是否ready
  bool check_parameter(int t);	

  bool save_parameter();
  
  //测试函数
  std::string get_ip();

 private:
  //需要持有master信息                                                                                                                     
  std::string master_ip_;
  int master_port_;
  //需要在指定端口下启动参数服务器
  int parameter_server_port_;
  //需要建立和master的客户端接收任务
  shared_ptr<MLtaskClient> task_;
  shared_ptr<TTransport> transport_;
  //需要保存参数服务器的指针
  shared_ptr<::apache::thrift::server::TThreadPoolServer> parameter_server_;
  //需要接收从master传来的任务
  task::ServerTask server_task_;
  //参数表示
  using Key = std::string;
  using Value = ParameterValue*;
  std::unordered_map<Key,Value> parameter_;
  //保存参数服务器handler指针向他传递任务
  shared_ptr<ParameterServerHandler> handler_;
  //Optimizer optimizer_;
};

#endif
