//所有信息均由protobuf进行序列化反序列化，thrift只传输string（序列化后的容器）
service MLtask{
  //model向master提交任务的请求，string为序列化后的networkstruct和distinfo
  //序列化应该使用binary instead of string, 避免encode问题
  bool submit(1:binary dist_info, 2:binary network_struct),

  //model会查询目前的任务进度
  binary query(),

  //worker请求注册,需要返回其id
  i32 worker_regist_to_master(),

  //worker需要loop来请求计算任务
  //返回计算任务以及需要连接到的server组信息
  binary worker_ask_for_task(),

  //worker需要提交第t轮的计算任务结果，
  void worker_submit_kth_result(1:binary kth_result),

  //server发送自己的身份信息,不需要得到信息
  void server_regist_to_master(1:binary server_info),

  //server同样需要loop接收计算任务，
  binary server_ask_for_task()
}
