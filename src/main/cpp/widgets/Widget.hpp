#pragma once

#include <string>
#include <optional>
#include "../Console.hpp"

namespace Blame::Widgets {
    class Widget {
    public:
        Widget(Console *console, std::optional<Blame::Widgets::Widget*> parent, int column, int row, int width, int height);

        virtual void redraw();
        void setColours();

    protected:
        Console *console;
        std::optional<Blame::Widgets::Widget*> parent;

        int column;
        int row;
        int width;
        int height;

        int padding_top;
        int padding_left;
        int padding_right;
        int padding_bottom;

        int internal_padding_top;
        int internal_padding_left;
        int internal_padding_right;
        int internal_padding_bottom;

        std::string colour_border;
        std::string colour_background;
        std::string colour_text;

        std::string symbol_top_left;
        std::string symbol_top_middle;
        std::string symbol_top_right;
        std::string symbol_middle_left;
        std::string symbol_middle_fill;
        std::string symbol_middle_right;
        std::string symbol_bottom_left;
        std::string symbol_bottom_middle;
        std::string symbol_bottom_right;
    };
}