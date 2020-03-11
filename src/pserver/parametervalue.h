#ifndef PARAMETERVALUE_H
#define PARAMETERVALUE_H

#include<vector>
#include<string>
#include<random>

enum DataType {int8, float32, float16};

//数据基类可扩展成vector matrix tensor..
class ParameterValue{
 public:
  ParameterValue(DataType data_type, const std::vector<uint32_t>& shape)
    : data_type_(data_type), shape_(shape){}
  
  virtual ~ParameterValue();

  //TODO限定赋值范围和类型
  virtual void set_random(float upper_bound, float lower_bound);

  DataType data_type_;

  std::vector<uint32_t> shape_;

};


class VectorParameter : public ParameterValue{
 public:
  VectorParameter(DataType data_type, const std::vector<uint32_t>& shape)
   : ParameterValue(data_type, shape) {
     values.resize(shape[0]);
   }
  
  void set_random(float upper_bound, float lower_bound){
    std::default_random_engine random;
    std::uniform_real_distribution<float> range(upper_bound, lower_bound);
    const size_t size = values.size();
    for(size_t i = 0; i < size; i++){
      values[i] = range(random);
    }
  }

  //TODO暂定只实现float
  std::vector<float> values;
};

class VectorParameter : public ParameterValue{
 public:
  VectorParameter(DataType data_type, const std::vector<uint32_t>& shape)
   : ParameterValue(data_type, shape) {
     if(shape.size() != 1){
       throw "size does not match 1-D vector!";
     }
     values.resize(shape[0]);
   }
  
  void set_random(float upper_bound, float lower_bound){
    std::default_random_engine random;
    std::uniform_real_distribution<float> range(upper_bound, lower_bound);
    const size_t size = values.size();
    for(size_t i = 0; i < size; i++){
      values[i] = range(random);
    }
  }

  //TODO暂定只实现float
  std::vector<float> values;
};

class MatrixParameter : public ParameterValue{

  //构造函数
 public:
  MatrixParameter(DataType data_type, const std::vector<uint32_t>& shape)
   : ParameterValue(data_type, shape) {
     //判断size是否符合2-D
     if(shape.size() != 2){
       throw "size does not match 2-D matrix!";
     }
     values.resize(shape[0]);
     for(uint32_t row = 0; row < shape[0]; row++){
       values[row].resize(shape[1]);
     }
   }
  
  //随机赋值
  void set_random(float upper_bound, float lower_bound){
    std::default_random_engine random;
    std::uniform_real_distribution<float> range(upper_bound, lower_bound);
    const size_t row = values.size();
    const size_t column = values[0].size();
    for(size_t i = 0; i < row; i++){
      for(size_t j = 0; j < column; j++){
        values[i][j] = range(random);
      }
    }
  }

  //TODO暂定只实现float
  std::vector<std::vector<float>> values;
};
#endif