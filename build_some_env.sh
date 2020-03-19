#protoc -I=./proto --cpp_out=./src/common worker_task.proto
thrift -r --gen cpp  -o ./src/common ./idl/thrift/task.thrift
thrift -r --gen cpp  -o ./src/common ./idl/thrift/parameter_server.thrift
thrift -r --gen py  -o ./src/common ./idl/thrift/task.thrift
protoc -I=./proto --cpp_out=./src/common transport_info.proto
protoc -I=./proto --cpp_out=./src/common parameter_server.proto
protoc -I=./proto --python_out=./src/common transport_info.proto