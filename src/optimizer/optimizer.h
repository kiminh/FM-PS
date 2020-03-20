#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include"../pserver/parametervalue.h"
#include<memory>
#include<glog/logging.h>

#include<iostream>

using namespace std;

class SgdOptimizer{
 public:
  SgdOptimizer(){}

  void update(std::shared_ptr<ParameterValue> parameter, std::shared_ptr<ParameterValue> gradient, float learning_rate){
    const size_t size = parameter->get_values().size();
    if(size != gradient->get_values().size()){
      LOG(ERROR) << "size does not match";
      LOG(INFO) << "paramter size: " << size;
      LOG(INFO) << "gradient size: " << gradient->get_values().size();
      return;
    }
    for(size_t i = 0; i < size; i++){
      float before = (*parameter).values[i];
      //LOG(INFO) << learning_rate << " " << (*gradient).values[i];
      (*parameter).values[i] = (*parameter).values[i] - learning_rate * (*gradient).values[i];
      //LOG(INFO) << "更新了:" << (*parameter).values[i] - before;
    }
  }
};

#endif