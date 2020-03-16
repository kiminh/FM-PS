#ifndef PSERVER_H
#define PSERVER_H

//c_and_c++头文件
#include<string>
#include<unordered_map>
#include<thread>

//其他库头文件
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/server/TThreadPoolServer.h>

//本项目头文件
//TODO
//风格需要修正，避免使用类似 .. .等快捷路径
#include"../common/gen-cpp/MLtask.h"
#include"../common/transport_info.pb.h"
#include"../common/nodeinfo.h"
#include"parametervalue.h"
#include"parameter_server_handler.h"

//Pserver
//功能:
//1.提供当前本机通讯信息(ip以及port)给远端的Master
//2.从Master端获取参数结构以及相关任务信息(记载在/proto/transport_info.proto中的ServerTask)
//3.作为thrift server提供parameter给远端的若干TWorker计算节点
//4.接收从TWorker传输来的第t轮的梯度，并通过优化器进行最新的参数更新

//使用说明
//PS：
//如何在main.cpp中使用Pserver
//1.构造出一个Pserver对象
//说明:通过deploy.sh脚本传递master ip 和 port以及指定一个可用的参数服务器端口
//std::shared_ptr<Pserver> server = make_shared<Pserver>(ip, port, server_port);
//2.构建参数服务器
//说明:Pserver不仅作为参数服务器(for Tworker)，也作为客户端(to Master)
//因此在与Master通信之前需要确保参数服务器先建立起来，因为Tworker在收到
//需要通信的参数服务器的信息之后，就会请求服务，这个时候并不希望它连接的参数
//服务器还没有建立
//TODO:需要思考有哪些异常点需要考虑
//try{
//  server->build_parameter_server();
// }catch(){
//   //异常处理
// }
//3.连接到Master端
//说明:Master端先于Pserver端启动，
//因此使用的下一步便是"注册到Master"(发送自己的通讯信息，对应了功能的第一点)
//当然在注册之前首先需要连接到master连接之后就可以立马注册所以只需要调用
//TODO:仍然是需要思考要抛出哪些异常
//try{
//  server->build_client_and_connect_to_master();
//}catch(Exception){
//
//}
//4.向master发送自身信息以提供给Tworker
//说明：此步为注册到master端,这是server第一次对master的RPC调用
//作为server并不需要master在注册时返回信息
//server->regist_to_master();
//TODO:通过一个较大的函数控制下列的服务server的所有流程，提供方便(统一)的接口
//5.向Master请求任务
//说明:目前参数服务器仍然没有启动服务，这是因为
//参数服务器所需要的参数和任务仍然为空，即使开启服务也不能做任何的事情
//因此下一步自然是需要请求Master分配对应的任务到Pserver
//通过loop请求任务，直到任务不为空则退出
//server->ask_for_task();
//6.加载参数以及传输任务给参数服务器(parameter_server_)
//说明:请求任务函数退出时，说明已经有或大或小的任务数据从Master返回
//此时需要Pserver根据返回的参数格式加载参数到内存，并把对应的参数以及其他所需要的
//任务信息传递给ParameterServerHandler(负责响应Tworker端的RPC请求)
//并开启ParameterServer的服务
//TODO:实现该功能
//至此，Pserver可以与Tworker协同进行分布式机器学习的训练
//7.移步至ParameterServerHandler
//它是主要的提供服务的功能类
//TODO:参数结构ParameterValue对象的多线程保护（安全）
//TODO:3-D及以上参数的表示(up to 5-D)
//TODO:Pserver不同机器学习算法的实现(同步控制)
//TODO:etc
class Pserver{
 public:
  //构造
  Pserver(const std::string& master_ip, int master_port, int parameter_server_port);

  //启动一个线程去执行以下任务:
  // server->build_client_and_connect_to_master();
  // server->regist_to_master();
  // server->ask_for_task();
  // server->load_parameter_to_memory();
  // server->print_in_memory_parameter();
  //并且将必要的数据传给parameterserverhandler
  //对于该线程来说是不需要等待它执行完毕的，所以不需要join,而是detach
  void init_sub_task_thread();

  //与Master交互任务以及提供任务信息给parameter_server_handler任务的集合
  static void building_connecting_deliver_tasks(void* __this);
  
  //调用建立参数服务器的user是main，因此如果建立不成功就要抛出异常给它
  //成功的话只是把参数服务器建立起来，不需要返回什么信息给它
  void build_parameter_server();

  void build_client_and_connect_to_master();

  //如果注册失败则返回失败否则注册成功
  bool regist_to_master();

  //loop请求master响应任务
  //并将返回的信息存入ServerTask
  void ask_for_task();

  //使参数服务器开始提供服务
  void start_serve();

  //获取ip
  std::string get_ip();

 private:
  //需要持有master信息                                                                                                                     
  std::string master_ip_;
  int master_port_;
  //需要在指定端口下启动参数服务器
  int parameter_server_port_;
  //需要建立和master的客户端接收任务
  std::shared_ptr<MLtaskClient> task_;
  std::shared_ptr<::apache::thrift::transport::TTransport> transport_;
  //需要保存参数服务器的指针
  std::shared_ptr<::apache::thrift::server::TThreadPoolServer> parameter_server_;
  //保存参数服务器handler指针向他传递任务
  std::shared_ptr<ParameterServerHandler> handler_;
};

#endif
