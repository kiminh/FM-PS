#include"../../src/master/master.h"

#include<iostream>

using namespace std;

int main(int argc, char** argv){
  Master* master = new Master(atoi(argv[1]));  
  cout << "Master 启动" << endl;
  master->start_serve();
  return 0;
}