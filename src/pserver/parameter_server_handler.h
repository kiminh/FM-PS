#ifndef PARAMETER_SERVER_HANDLER_H
#define PARAMETER_SERVER_HANDLER_H

//TODO风格修正 避免 .. 快捷路径
#include "../common/gen-cpp/ParameterServer.h"
#include"../common/transport_info.pb.h"
#include"../common/parameter_server.pb.h"

#include<string>
#include<unordered_map>

#include"parametervalue.h"

#include<glog/logging.h>

//作为参数服务器的核心，它存在于pserver的一个数据成员
//pserver会在收到任务之后通过某个接口将初始化好的参数传入
//因此，该类需要能接收参数的表示
class ParameterServerHandler : virtual public ParameterServerIf {
 public:
  ParameterServerHandler(){}

  void pull(std::string& _return, const int32_t epoch);

  void push(const int32_t epoch, const std::string& gradient);

  //接收任务信息
  void receive_task_from_pserver(const std::string& serialized_task);

  //根据SeverTask中的信息加载对应参数到parameters_
  void load_parameter_to_memory();

  //检验参数的加载情况
  void print_in_memory_parameter();

 private:
 //控制现在进行到的epoch
  int32_t current_epoch;
  //目标需要更新的轮数 
  int32_t target_epoch;
  //优化器
  //Optimizer optimizer_;

  //直接在接收任务时接收到这里
  task::ServerTask task_;

  //参数表示
  //@para string 参数的key
  //@para Parameter基类的指针， 动态绑定为对应参数
  std::unordered_map<std::string, ParameterValue*> parameters_;

  //序列化现有参数
  std::string serialize();
  
};
#endif