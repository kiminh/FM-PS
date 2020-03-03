#cmake_minium_required(VERSION 3.10)

#项目名称
project(FM-PS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)

#需要编译entry中两个cpp文件
add_executable(master ./entry/cpps/master.cpp)
add_executable(server ./entry/cpps/pserver.cpp)
