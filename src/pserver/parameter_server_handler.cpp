#include"parameter_server_handler.h"


std::string ParameterServerHandler::serialize(){ 
  ;
}

void ParameterServerHandler::pull(std::string& _return, const int32_t epoch){
  //如果是同步，那么可以在每一轮结束之后完成一次序列化参数，然后每个worker都拿到一样的
  //如果是异步，那么就是要每个worker都要进行一次序列化
  //因此需要一个序列化函数
  ;
}

void ParameterServerHandler::push(const int32_t epoch, const std::string& gradient){
  ;
}

