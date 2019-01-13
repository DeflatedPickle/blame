cmake_minimum_required(VERSION 3.13)
project(blame)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(include)

target_include_directories(blame_src PUBLIC
        src/main/cpp
        include)

target_link_libraries(blame_src stdc++fs)

add_subdirectory(demos)