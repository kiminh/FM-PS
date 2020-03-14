#include"../../src/master/master.h"

#include<glog/logging.h>
#include<iostream>

using namespace std;

int main(int argc, char** argv){
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;
  LOG(INFO) << "准备创建master";
  Master* master = new Master(atoi(argv[1]), 3, 3);  
  LOG(INFO) << "Master 启动";
  master->start_serve();
  return 0;
}
