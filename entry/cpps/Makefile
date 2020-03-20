common_path = ../../src/common/
common_cpp_path = ../../src/common/gen-cpp/
src_master_path = ../../src/master/
src_server_path = ../../src/pserver/
master_entry:
	g++ -g -O3 \
	$(common_path)transport_info.pb.cc \
	$(common_cpp_path)MLtask.cpp \
	$(src_master_path)mltaskhandler.cpp \
	$(src_master_path)master.cpp \
	master_entry.cpp \
	-lprotobuf -lthrift -lglog \
	-o master_entry

server_entry:
	g++ -g -O3 \
	$(common_path)transport_info.pb.cc \
	$(common_path)parameter_server.pb.cc \
	$(common_cpp_path)MLtask.cpp \
	$(src_server_path)parameter_server_handler.cpp \
	$(common_cpp_path)ParameterServer.cpp \
	$(src_server_path)pserver.cpp \
	pserver_entry_multithread.cpp \
	-o server_entry -lthrift -lprotobuf -lglog -lpthread
clean:
	rm server_entry master_entry