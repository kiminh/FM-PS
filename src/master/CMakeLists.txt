#TODO
add_subdirectory(../../proto)
add_library(Master master.cpp)
target_link_libraries(Master proto)
