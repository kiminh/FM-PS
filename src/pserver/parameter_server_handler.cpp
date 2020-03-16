#include"parameter_server_handler.h"


std::string ParameterServerHandler::serialize(){ 
  task::ParametersOrGradients newest_parameters;
  for(auto iterator = parameters_.begin(); iterator != parameters_.end(); iterator++){
    auto pair = newest_parameters.add_pairs();
    pair->set_name((*iterator).first);
    ParameterValue* value = (*iterator).second;
    pair->set_dim(value->shape_.size());
    for(int i = 0; i < value->shape_.size(); i++){
      pair->add_shape(value->shape_[i]);
    }
    //添加参数为一个一维的数组
    const std::vector<float>& value_array = value->get_values();
    const size_t value_size = value_array.size();
    for(int i = 0; i < value_size; i++){
      pair->add_values(value_array[i]);
    }
  }
  std::string serialized_parameter;
  if(!newest_parameters.SerializeToString(&serialized_parameter)){
    LOG(ERROR) << "序列化最新参数失败";
    return "";
  }
  return serialized_parameter;
}

void ParameterServerHandler::pull(std::string& _return, const int32_t epoch){
  //TODO:控制参数是否可用
  _return = serialize();
}

void ParameterServerHandler::push(const int32_t epoch, const std::string& gradient){
  LOG(INFO) << "收到来自worker的梯度";
}

void ParameterServerHandler::receive_task_from_pserver(const std::string& serialized_task){
  task_.ParseFromString(serialized_task); 
}

//对于每一个参数构建一个对象（vector 或者矩阵）
//进行初始化，建立这个映射
void ParameterServerHandler::load_parameter_to_memory(){
  //TODO,目前默认初始化为随机初始化
  float upper_bound = 1.0;
  float lower_bound = 0.0;
  for(int i = 0; i < task_.parameter_list_size(); i++){
    const task::Parameter& parameter = task_.parameter_list(i);
    //根据dim判断类型
    //随机赋值后加入哈希表
    if(1 == parameter.dim()){
      /*
      shared_ptr<VectorParameter> value 
          = make_shared<VectorParameter>(parameter.data_type(), {parameter.shape(0)});
      value->set_random(upper_bound, lower_bound);*/
      VectorParameter* value = new VectorParameter(1, {parameter.shape(0)});
      //shared_ptr<VectorParameter> value = make_shared<VectorParameter>(1, {parameter.shape(0)});
      value->set_random(upper_bound, lower_bound);
      parameters_[parameter.key()] = value;
    }
    else if(2 == parameter.dim()){
      /*shared_ptr<MatrixParameter> value 
        = make_shared<MatrixParameter>(1, {parameter.shape(0), parameter.shape(1)});*/
      MatrixParameter* value = new MatrixParameter(1, {parameter.shape(0), parameter.shape(1)});
      value->set_random(upper_bound,lower_bound);
      parameters_[parameter.key()] = value;
    }
  }
}

void ParameterServerHandler::print_in_memory_parameter(){
  for(auto iterator = parameters_.begin(); iterator != parameters_.end(); iterator++){
    LOG(INFO) << (*iterator).first;
    ParameterValue* value = (*iterator).second;
    const int dim = value->shape_.size();
    LOG(INFO) << "是" << dim << "维的参数";
    LOG(INFO) << "值为:";
    value->print_value();
  }
}