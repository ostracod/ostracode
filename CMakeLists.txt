
cmake_minimum_required(VERSION 3.15)
project(ostracode CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(ostracode ${SOURCES})
target_link_libraries(ostracode JsonCpp::JsonCpp)


