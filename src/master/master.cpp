#include"master.h"

#include<iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

Master::Master(int port, uint32_t num_workers, uint32_t num_servers)
   : port_(port), num_workers_(num_workers), num_servers_(num_servers){}

void Master::start_serve(){
  shared_ptr<MLtaskHandler> handler(new MLtaskHandler(num_workers_, num_servers_));
  shared_ptr<TProcessor> processor(new MLtaskProcessor(handler));
  shared_ptr<TServerTransport> server_transport(new TServerSocket(port_));
  shared_ptr<TTransportFactory> transport_factory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocol_factory(new TBinaryProtocolFactory());
  task_server_ = new TSimpleServer(processor, server_transport, transport_factory, protocol_factory);
  cout << "Master start serve at port: " << port_ << endl;
  task_server_->serve();
}
