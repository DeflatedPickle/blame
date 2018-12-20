cmake_minimum_required(VERSION 3.13)
project(blame_src)

set(CMAKE_CXX_STANDARD 17)

add_library(blame_src
        main/cpp/Console.cpp
        main/cpp/Console.hpp

        main/cpp/util/EscapeCodes.hpp

        main/cpp/widgets/Widget.cpp
        main/cpp/widgets/Widget.hpp

        main/cpp/widgets/Window.cpp
        main/cpp/widgets/Window.hpp
)