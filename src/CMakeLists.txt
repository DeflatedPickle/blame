cmake_minimum_required(VERSION 3.13)
project(blame_src)

set(CMAKE_CXX_STANDARD 17)

add_library(blame_src
        main/cpp/Console.cpp
        ../include/Console.hpp

        ../include/util/EscapeCodes.hpp
        ../include/util/State.hpp
        ../include/util/StateWindow.hpp

        main/cpp/widgets/Widget.cpp
        ../include/widgets/Widget.hpp

        main/cpp/widgets/Window.cpp
        ../include/widgets/Window.hpp

        ../include/util/Direction.hpp

        ../include/widgets/Listener.hpp

        ../include/util/ClientArea.hpp

        ../include/styles/Style.hpp
        ../include/styles/Symbols.hpp
        ../include/styles/Colours.hpp
        ../include/styles/StateColours.hpp

        ../include/styles/StyleWindow.hpp
        ../include/styles/StyleButton.hpp
        ../include/styles/StyleScaleHorizontal.hpp
        ../include/styles/StyleScaleVertical.hpp
        ../include/styles/StyleText.hpp

        main/cpp/widgets/Button.cpp
        ../include/widgets/Button.hpp

        ../include/widgets/managers/Manager.hpp
        ../include/widgets/managers/Pack.hpp

        main/cpp/widgets/Text.cpp
        ../include/widgets/Text.hpp

        main/cpp/widgets/Scale.cpp
        ../include/widgets/Scale.hpp

        main/cpp/widgets/List.cpp
        ../include/widgets/List.hpp)