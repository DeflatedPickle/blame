cmake_minimum_required(VERSION 3.12)
project(blame_demo_dim)

set(CMAKE_CXX_STANDARD 17)

add_executable(blame_demo_dim main.cpp)
target_link_libraries(blame_demo_dim LINK_PUBLIC blame_src)