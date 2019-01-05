cmake_minimum_required(VERSION 3.12)
project(blame_demo_widgets)

set(CMAKE_CXX_STANDARD 17)

add_executable(blame_demo_widgets main.cpp)
target_link_libraries(blame_demo_widgets LINK_PUBLIC blame_src)