#include"../../src/pserver/pserver.h"

#include<glog/logging.h>

using namespace std;

int main(int argc, char** argv){
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;
  shared_ptr<Pserver> server = make_shared<Pserver>(argv[1], atoi(argv[2]), atoi(argv[3]));
  LOG(INFO) << "server 启动";
  server->build_parameter_server();
  server->build_client_and_connect_to_master();
  server->regist_to_master();
  server->ask_for_task();
  server->load_parameter_to_memory();
  server->print_in_memory_parameter();
  server->start_serve();
  //TODO
  //加载参数后传给handler，由handler来控制是否能够提供参数
  return 0;
}
 
// 建立参数服务器函数
// try{
//   build_parameter_server();
// }
// catch{
//   终止服务
// }


//server(master_ip, master_port, pserver_port);
//建立参数服务器，如果在这里就挂了，那么注册的信息其实是无效的，因为worker没有办法
//进行交互，所以这里不成功就不建立与master 的客户端
//成功之后有了参数服务器（多线程），但参数服务器上没有参数可以拿
//因此要建立一个与master的客户端，loop等待任务，如果拿到任务了，那么退出这个函数
//参数服务器本质上就是要存储梯度更新梯度提供梯度而已，所以当更新完了最后一轮的参数
//存储完模型之后，任务就完成，这个时候要再回到要任务的阶段，因此master如何确保自己的任务不是已经
//执行过的呢，就是再全部发完之后设置任务不可用并清空，如果下次有任务又准备好了就可以
//继续分发任务

//需要有一个大函数来控制它的工作过程
//big_function(){
  //ask_for_task()
  //do_this_train()
  //end()
  //回到之前
  //那么什么时候停下来了，可能是master和server之间有一个交互，问是否停下服务
  //则退出循环结束该server的任务
//}

//所以现在需要设置一下和worker的参数服务器

//和worker的交互起始于worker请求第t轮的参数
//几个问题：判断参数是否可用，因为是多线程的服务器，所以先不管，再讨论
//可用怎么给它，以什么形式给它
//参数服务器是server的一个成员，要怎么把参数信息给进去呢，
//在pserver收到信息并且解析之后，可以把handler也作为一个成员，并且暴露一个public接口
//去接收任务

//优化器也要是个枚举类