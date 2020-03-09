#include"util.h"
#include<iostream>

int main(){
  std::string test("dense_5_w");
  std::string test2("conv_3_b");
  int server_num = 3;
  std::cout << hash_string_to_int(test) % server_num  << std::endl;
  std::cout << hash_string_to_int(test2) % server_num << std::endl;
  return 0;
}