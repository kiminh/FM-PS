#include"pserver.h"
#include<sys/socket.h>

#include<iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void Pserver::regist_to_master(){
  try{
    cout << master_ip_ << endl;
    cout << master_port_ << endl;
    shared_ptr<TTransport> socket(new TSocket(master_ip_, master_port_));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    task_ = new MLtaskClient(protocol);
    MLtaskClient task(protocol);
    transport->open();
    cout << "建立与master服务器的连接地址为" << master_ip_ << " " << to_string(master_port_) << endl;
  }
  catch(TException& tx){
    cout << "连接错误" << tx.what() << endl;
  }
  //打包本进程ip port
  task::ServerInfo my_info;
  //my_info.set_ip();
  //my_info.set_port();
}

void Pserver::ask_for_task(){
  string server_task;
  while(true){
    (*task_).server_ask_for_task(server_task);
    if("" != server_task) break;
    server_task_.ParseFromString(server_task);
  }
  //打印信息
  for(int i = 0; i < server_task_.parameter_list_size(); i++){
    const task::Parameter& parameter = server_task_.parameter_list(i);
    cout << parameter.key() << endl;
    for(int j = 0; j < parameter.shape_size(); j++){
      cout << parameter.shape(j) << " ";
    }
    cout << endl;
  }
}