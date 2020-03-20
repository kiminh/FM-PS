#include"../../src/pserver/pserver.h"

#include<glog/logging.h>

using namespace std;

int main(int argc, char** argv){
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;
  shared_ptr<Pserver> server = make_shared<Pserver>(argv[1], atoi(argv[2]), atoi(argv[3]));
  LOG(INFO) << "server 启动";
  server->build_parameter_server();
  server->init_sub_task_thread();
  server->start_serve();
  return 0;
}