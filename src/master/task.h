#ifndef TASK_H
#define TASK_H

#include<string>
#include<vector>

struct Tensor{
  std::string key;
  enum Data_type{int8, float16, float32, float64};
  uint32_t dim;
  uint32_t shape;
};

struct LayerInfo{
  std::string name;
  std::string activation;
  Tensor input;
  Tensor output;
};

//Task需要汇总所有从Model发来的计算任务
struct Task{
  //master-owned
  uint32_t num_workers;
  uint32_t num_servers;

  //worker_part
  std::string data_path;
  std::string data_division;
  uint32_t num_layers;
  uint32_t mini_batch_size;
  std::string loss;
  //network
  std::vector<LayerInfo> layer_info_;
    
  
  //server_part
  std::string model_division;
  std::string parameter_initialize;
  std::string parameter_load_path;
  std::string pata_store_path;		
  std::string optimizer;
  float learning_rate;
  //parameter
  std::vector<Tensor> parameter_info;
  
  //common
  uint32_t epoch;
  std::string consistency;
  std::string dataset;
};
#endif
