#include"../../src/pserver/pserver.h"

#include<iostream>

using namespace std;

int main(int argc, char** argv){
  auto server = new Pserver(argv[1], atoi(argv[2]));
  server->regist_to_master();
  cout << "server 启动" << endl;
  server->ask_for_task();
  return 0;
}