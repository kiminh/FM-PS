common_path = ../common/
common_cpp_path = ../common/gen-cpp/
server:
	g++ -g -O3 \
	$(common_path)transport_info.pb.cc \
	$(common_cpp_path)MLtask.cpp \
	parameter_server_handler.cpp \
	$(common_cpp_path)ParameterServer.cpp \
	pserver.cpp \
	-o server -lthrift -lprotobuf -lglog

clean:
	rm ./server