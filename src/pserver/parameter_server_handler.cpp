#include"parameter_server_handler.h"

using namespace std;

std::string ParameterServerHandler::serialize(){ 
  task::ParametersOrGradients newest_parameters;
  for(auto iterator = parameters_.begin(); iterator != parameters_.end(); iterator++){
    auto pair = newest_parameters.add_pairs();
    pair->set_name((*iterator).first);
    shared_ptr<ParameterValue> value = (*iterator).second;
    pair->set_dim(value->shape_.size());
    for(int i = 0; i < value->shape_.size(); i++){
      pair->add_shape(value->shape_[i]);
    }
    //添加参数为一个一维的数组
    const size_t value_size = value->values.size();
    for(int i = 0; i < value_size; i++){
      pair->add_values(value->values[i]);
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
  //LOG(INFO) << "收到来自worker的梯度";
  //反序列化
  task::ParametersOrGradients kth_gradient;
  kth_gradient.ParseFromString(gradient);
  const size_t size = kth_gradient.pairs_size();
  //遍历key-gradient pair
  for(size_t i = 0; i < size; i++){
    const task::KeyValuePair& pair = kth_gradient.pairs(i);
    const uint32_t pair_size = pair.values_size();
    vector<uint32_t> shape{pair_size};
    gradients_[pair.name()] =  make_shared<VectorParameter>(1, shape);
    for(int j = 0; j < pair_size; j++){
      gradients_[pair.name()]->values[j] = pair.values(j);
    }
  }
  //update
  update_parameter();
}

void ParameterServerHandler::update_parameter(){
  for(auto paramter = parameters_.begin(); paramter != parameters_.end(); paramter++){
    string key = (*paramter).first;
    if(!gradients_[key]){
      LOG(INFO) << "key为" << key << "的梯度不存在";
      return;
    }
    // else{
    //   LOG(INFO) << key << " " << gradients_[key]->values[10];
    // }
    shared_ptr<ParameterValue> gradient = gradients_[key];
    optimizer_.update((*paramter).second, gradient, task_.learning_rate());
  }
}

void ParameterServerHandler::receive_task_from_pserver(const std::string& serialized_task){
  task_.ParseFromString(serialized_task);
}

//对于每一个参数构建一个对象（vector 或者矩阵）
//进行初始化，建立这个映射
void ParameterServerHandler::load_parameter_to_memory(){
  //TODO,目前默认初始化为随机初始化
  //标准正态分布
  float u = 0.0;
  float v = 1.0;
  for(int i = 0; i < task_.parameter_list_size(); i++){
    const task::Parameter& parameter = task_.parameter_list(i);
    //根据dim判断类型
    //随机赋值后加入哈希表
    if(1 == parameter.dim()){
      vector<uint32_t> shape{parameter.shape(0)};
      shared_ptr<ParameterValue> value = make_shared<VectorParameter>(1, shape);
      value->set_random(u, v);
      parameters_[parameter.key()] = value;
    }
    else if(2 == parameter.dim()){
      vector<uint32_t> shape{parameter.shape(0), parameter.shape(1)};
      shared_ptr<ParameterValue> value = make_shared<MatrixParameter>(1, shape);
      value->set_random(u,v);
      parameters_[parameter.key()] = value;
    }
  }
}

void ParameterServerHandler::print_in_memory_parameter(){
  for(auto iterator = parameters_.begin(); iterator != parameters_.end(); iterator++){
    LOG(INFO) << (*iterator).first;
    shared_ptr<ParameterValue> value = (*iterator).second;
    const int dim = value->shape_.size();
    LOG(INFO) << "是" << dim << "维的参数";
    LOG(INFO) << "值为:";
    value->print_value();
  }
}