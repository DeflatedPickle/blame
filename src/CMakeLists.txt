cmake_minimum_required(VERSION 3.13)
project(blame_src)

set(CMAKE_CXX_STANDARD 17)

add_library(blame_src
        main/cpp/Console.cpp
        main/cpp/Console.hpp

        main/cpp/util/EscapeCodes.hpp
        main/cpp/util/State.hpp

        main/cpp/widgets/Widget.cpp
        main/cpp/widgets/Widget.hpp

        main/cpp/widgets/Window.cpp
        main/cpp/widgets/Window.hpp

        main/cpp/util/Direction.hpp

        main/cpp/widgets/Listener.hpp

        main/cpp/util/ClientArea.hpp

        main/cpp/styles/Style.hpp
        main/cpp/styles/Symbols.hpp
        main/cpp/styles/Colours.hpp

        main/cpp/styles/StyleWindow.hpp
        main/cpp/styles/StyleButton.hpp

        main/cpp/widgets/Button.cpp
        main/cpp/widgets/Button.hpp

        main/cpp/widgets/managers/Manager.hpp
        main/cpp/widgets/managers/Pack.hpp main/cpp/widgets/Text.cpp main/cpp/widgets/Text.hpp)