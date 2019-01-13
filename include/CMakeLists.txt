cmake_minimum_required(VERSION 3.13)
project(blame_include)

set(CMAKE_CXX_STANDARD 17)

add_library(blame_include
        Console.hpp

        util/EscapeCodes.hpp
        util/State.hpp
        util/StateWindow.hpp

        widgets/Widget.hpp

        widgets/Window.hpp

        util/Direction.hpp

        widgets/Listener.hpp

        util/Area.hpp

        styles/Style.hpp
        styles/Symbols.hpp
        styles/Colours.hpp
        styles/StateColours.hpp

        styles/StyleWindow.hpp
        styles/StyleButton.hpp
        styles/StyleScaleHorizontal.hpp
        styles/StyleScaleVertical.hpp
        styles/StyleText.hpp

        widgets/Button.hpp

        widgets/managers/Manager.hpp
        widgets/managers/Pack.hpp

        widgets/Text.hpp

        widgets/Scale.hpp

        widgets/List.hpp)

set_target_properties(blame_include PROPERTIES LINKER_LANGUAGE CXX)