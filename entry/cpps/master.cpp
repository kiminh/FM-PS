#include"../../src/master/master.h"

#include<iostream>

using namespace std;

int main(int argc, char** argv){
  Master(atoi(argv[1]));  
  cout << "Master 启动" << endl;
  return 0;
}