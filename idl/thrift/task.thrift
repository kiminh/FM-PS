//所有信息均由protobuf进行序列化反序列化，thrift只传输string（序列化后的容器）
service MLtask{
  //model向master提交任务的请求，string为序列化后的networkstruct和distinfo
  bool submit(1:string task),
  //model会查询目前的任务进度
  string query(),
  //worker发送自己的ip和port向master注册，（若当前信息不可用则返回空）需要返回其id
  string worker_regist_to_master(1:string worker_info),
  //worker需要loop来请求计算任务
  //返回计算任务以及需要连接到的server组信息
  string worker_ask_for_task(),
  //worker需要提交第t轮的计算任务结果，
  void worker_submit_kth_result(1:string kth_result),
  //server发送自己的身份信息得到它的rank(在这里就是id)(负责哪一部分的参数)
  string server_regist_to_master(1:string server_info),
  //server同样需要loop接收计算任务，
  string server_ask_for_task()
}
