#ifndef PARAMETERVALUE_H
#define PARAMETERVALUE_H

#include<vector>
#include<string>
#include<random>
#include<iostream>

//TODO
//enum DataType {int8 = 0, float32 = 1, float16 = 2};

//数据基类可扩展成vector matrix tensor..
class ParameterValue{
 public:
  ParameterValue(int data_type, const std::vector<uint32_t>& shape)
    : data_type_(data_type), shape_(shape){}
  
  //virtual ~ParameterValue();

  //TODO限定赋值范围和类型
  virtual void set_random(float u, float v) = 0;

  virtual void print_value() = 0;

  virtual std::vector<float>& get_values() = 0;

  int data_type_;

  std::vector<uint32_t> shape_;

  std::vector<float> values;

};


class VectorParameter : public ParameterValue{
 public:
  VectorParameter(int data_type, const std::vector<uint32_t>& shape)
   : ParameterValue(data_type, shape) {
     values.resize(shape[0]);
   }
  
  void set_random(float u, float v){
    //从标准正太分布产生随机数
    std::random_device rd;
    std::default_random_engine random(rd());
    std::normal_distribution<float> range(u,v);
    const size_t size = values.size();
    for(size_t i = 0; i < size; i++){
      values[i] = range(random);
    }
  }

  void print_value(){
    for(int i = 0; i < 10; i++){
      std::cout << values[i] << " ";
    }
    std::cout << std::endl;
  }

  std::vector<float>& get_values(){
    return values;
  }

};

class MatrixParameter : public ParameterValue{

  //构造函数
 public:
  MatrixParameter(int data_type, const std::vector<uint32_t>& shape)
   : ParameterValue(data_type, shape) {
     //判断size是否符合2-D
     if(shape.size() != 2){
       throw "size does not match 2-D matrix!";
     }
     matrix_values.resize(shape[0]);
     for(uint32_t row = 0; row < shape[0]; row++){
       matrix_values[row].resize(shape[1]);
     }
   }
  
  //随机赋值
  void set_random(float u, float v){
    //从标准正太分布产生随机数
    std::random_device rd;
    std::default_random_engine random(rd());
    std::normal_distribution<float> range(u,v);
    const size_t row = matrix_values.size();
    const size_t column = matrix_values[0].size();
    for(size_t i = 0; i < row; i++){
      for(size_t j = 0; j < column; j++){
        matrix_values[i][j] = range(random);
        values.push_back(matrix_values[i][j]);
      }
    }
  }
  
  void print_value(){
    for(int i = 0; i < 10; i++){
      std::cout << values[i] << std::endl;
    }
 }

  std::vector<float>& get_values(){
    return values;
  }
 
 //private:
  //TODO暂定只实现float
  std::vector<std::vector<float>> matrix_values;
};
#endif