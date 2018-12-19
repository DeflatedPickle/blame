#pragma once

#include <string>
#include "Widget.hpp"

namespace Blame::Widgets {
    class Window : Widget {
    public:
        Window(Console *console, std::string title_text, int column, int row, int width, int height);

        void redraw() override;

    protected:
        std::string title_text;

        char symbol_title_top_left;
        char symbol_title_top_middle;
        char symbol_title_top_right;
        char symbol_title_middle_left;
        char symbol_title_middle_fill;
        char symbol_title_middle_right;
        char symbol_title_bottom_left;
        char symbol_title_bottom_middle;
        char symbol_title_bottom_right;

        char symbol_minimize;
        char symbol_maximize;
        char symbol_restore;
        char symbol_close;
    };
}