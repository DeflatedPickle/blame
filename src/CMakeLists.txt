cmake_minimum_required(VERSION 3.13)
project(blame_src)

set(CMAKE_CXX_STANDARD 17)

add_library(blame_src
        main/cpp/Console.cpp

        main/cpp/widgets/Widget.cpp

        main/cpp/widgets/Window.cpp

        main/cpp/widgets/Button.cpp

        main/cpp/widgets/Text.cpp

        main/cpp/widgets/Scale.cpp

        main/cpp/widgets/List.cpp

        main/cpp/widgets/Scroll.cpp
        
        main/cpp/widgets/Scrollable.cpp)
