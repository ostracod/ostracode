
cmake_minimum_required(VERSION 3.15)
project(ostracode CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

add_executable(ostracode src/main.cpp)
target_link_libraries(ostracode JsonCpp::JsonCpp)


