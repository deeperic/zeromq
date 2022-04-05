cmake_minimum_required(VERSION 3.21)
project(sub)

set(CMAKE_CXX_STANDARD 20)

add_executable(sub main.cpp)

find_package(cppzmq)
target_link_libraries(sub cppzmq)
