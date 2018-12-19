cmake_minimum_required(VERSION 3.12)
project(blame_demo)

set(CMAKE_CXX_STANDARD 17)

add_executable(blame_demo main.cpp)
target_link_libraries(blame_demo LINK_PUBLIC blame_src)