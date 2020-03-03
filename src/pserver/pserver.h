#ifndef PSERVER_H
#define PSERVER_H
//构造函数
//Pserver(const string& master_ip, int master_port){};
//构造之初首先要作为客户端连接到Master，因此也需要创建一个MLtaskClient
//同时作为服务端提供参数给Tworker因此需要建立一个服务端TSimpleServer
//保存自己的ip port到NodeInfo

//void regist_to_master();
//得到响应后得到id,添加到NodeInfo
#include<string>
#include<unordered_map>

#include"../common/gen-cpp/MLtask.h"
#include"../common/transport.pb.h"
#include"../common/nodeinfo.h"

#include <thrift/server/TSimpleServer.h>

class Pserver{
 public:
  //构造
  Pserver(const std::string& master_ip, int master_port){}

  void regist_to_master();

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
  
 private:
  //MLtaskClient task_;
  //::apache::thrift::server::TSimpleServer para_server_;
  NodeInfo server_;
  //task::ServerTask server_task_;
  //eigen c++算法库（待学习）
  //TODO
  //std::unordered_map<Key,Value> parameter_;
  //TODO
  //Optimizer optimizer_;
};

#endif
