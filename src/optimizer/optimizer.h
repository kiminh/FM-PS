#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include"parametervalue.h"
#include<memory>

class SgdOptimizer{
 public:

  SgdOptimizer();

  void update(std::shared_ptr<ParameterValue> parameter,
                             std::shared_ptr<ParameterValue> gradient, float learning_rate);
};

#endif