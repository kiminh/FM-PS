#ifndef TASK_H
#define TASK_H

#include<string>

using namespace std;

struct Tensor{
	string data_type;
	uint32_t dim;
	uint32_t shape;
};

struct LayerInfo{
	string name;
	string activation;
	Tensor input;
	Tensor output;
};

struct ParameterInfo{
	string key;
	Tensor shape; 
}

//Task需要汇总所有从Model发来的计算任务
struct Task{
	//master-owned
	uint32_t num_workers;
	uint32_t num_servers;

	//worker_part
	string data_path;
	string data_division;
	uint32_t num_layers;
	uint32_t mini_batch_size;
	string loss;
	//network
	vector<LayerInfo> layer_info_;
		
	
	//server_part
	string model_division;
  bool load_or_create;
  string para_initialize;
  string para_load_path;
  string pata_store_path;		
	string optimizer;
	string learning_rate;
	//parameter
	vecotr<ParameterInfo> parameter_info;
	
	//common
	uint32_t epoch;
	string consistency;
};
#endif
