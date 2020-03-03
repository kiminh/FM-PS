#生成依赖的头文件
thrift -r --gen cpp  -o ./src/common ./idl/thrift/task.thrift
protoc -I=./proto --cpp_out=./src/common transport.proto

mkdir build && cd build
cmake ..
make
