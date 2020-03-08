#include"master.h"

#include<iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

class MLtaskHandler : virtual public MLtaskIf {
 public:
  MLtaskHandler() : num_registed_worker_(0) {}

  bool submit(const std::string& dist_info, const std::string& network_struct) {
    //承接receive_task任务
    //把提交的序列化的dist_info反序列化并存储到task
    bool deserialize_dist_info_success = dist_info_.ParseFromString(dist_info);
    bool deserialize_network_struct = network_struct_.ParseFromString(network_struct);
    if(! deserialize_dist_info_success || !deserialize_network_struct){
      cout << "反序列化分布式信息" << deserialize_dist_info_success << endl;
      cout << "反序列化网络结构" << deserialize_network_struct << endl;
      return false;
    }
    cout << "提交了数据路径：" << dist_info_.data_path() << endl;
    cout << "提交了数据集处理任务" << dist_info_.dataset() << endl;
    task_.dataset = dist_info_.dataset();
    task_.data_path = dist_info_.data_path();
    network_struct_.ParseFromString(network_struct);
    return true;
  }

  void query(std::string& _return) {
    // Your implementation goes here
    printf("query\n");
  }

  void worker_regist_to_master(std::string& _return, const std::string& worker_info) {
    //TODO更改接口应该为uint
    string id = to_string(num_registed_worker_++);
    _return = id;
  }

  void worker_ask_for_task(std::string& _return) {
    //Task 信息序列化到WorkerTask(protobuf对象)
    task::WorkerTask worker_task;
    worker_task.set_data_path(task_.data_path);
    worker_task.set_dataset(task_.dataset);
    cout << worker_task.data_path() << endl;
    cout << worker_task.dataset() << endl;
    //序列化为字符串
    string serialized_task;
    if(!worker_task.SerializeToString(&serialized_task)){
      cout << "序列化worker任务失败" << endl;
    }
    cout << "任务字节数：" << serialized_task.length() << endl;
    //返回
    _return = serialized_task;
  }

  void worker_submit_kth_result(const std::string& kth_result) {
    // Your implementation goes here
    printf("worker_submit_kth_result\n");
  }

  void server_regist_to_master(std::string& _return, const std::string& server_info) {
    // Your implementation goes here
    printf("server_regist_to_master\n");
  }

  void server_ask_for_task(std::string& _return) {
    // Your implementation goes here
    printf("server_ask_for_task\n");
  }

 private:
  task::DistInfo dist_info_;
  task::NetworkStruct network_struct_;
  Task task_;
  uint32_t num_registed_worker_;
  uint32_t num_should_regist_worker;
};

void Master::start_serve(){
  shared_ptr<MLtaskHandler> handler(new MLtaskHandler());
  shared_ptr<TProcessor> processor(new MLtaskProcessor(handler));
  shared_ptr<TServerTransport> server_transport(new TServerSocket(port_));
  shared_ptr<TTransportFactory> transport_factory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocol_factory(new TBinaryProtocolFactory());
  task_server_ = new TSimpleServer(processor, server_transport, transport_factory, protocol_factory);
  cout << "Master start serve at port: " << port_ << endl;
  task_server_->serve();
}
