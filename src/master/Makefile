common_path = ../common/
common_cpp_path = ../common/gen-cpp/
master:
	g++ -g -O3 \
	$(common_path)transport_info.pb.cc \
	$(common_cpp_path)MLtask.cpp \
	mltaskhandler.cpp \
	master.cpp \
	-o master -lthrift -lprotobuf -lglog