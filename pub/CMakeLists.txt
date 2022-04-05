cmake_minimum_required(VERSION 3.21)
project(pub)

set(CMAKE_CXX_STANDARD 20)

add_executable(pub main.cpp)


find_package(cppzmq)
target_link_libraries(pub cppzmq)
