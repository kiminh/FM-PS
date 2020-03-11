#include"../../src/master/master.h"

#include<glog/logging.h>

using namespace std;

int main(int argc, char** argv){
  Master* master = new Master(atoi(argv[1]), 3, 3);  
  LOG(INFO) << "Master 启动";
  master->start_serve();
  return 0;
}
