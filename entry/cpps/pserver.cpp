#include"../../src/pserver/pserver.h"

#include<iostream>

using namespace std;

int main(int argc, char** argv){
  Pserver(argv[1], atoi(argv[2]));
  cout << "server 启动" << endl;
  return 0;
}