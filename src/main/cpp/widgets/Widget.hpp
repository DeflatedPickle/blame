#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include "../Console.hpp"
#include "Listener.hpp"
#include "../util/EscapeCodes.hpp"
#include "../util/State.hpp"

// TODO: Add checks for if the widget is focused or disabled
namespace Blame::Widgets {
    class Widget : public Blame::Widgets::Listener {
    public:
        Widget(Blame::Console *console, std::optional<Blame::Widgets::Widget*> parent);

        virtual void redraw();
        void setColours();

        void quit() override {}

        void focus() override {
            this->console->focused_widget = this;
            this->state = Blame::Util::State::FOCUSED;
        }

        void unfocus() override {
            this->state = Blame::Util::State::NORMAL;
        }

        void arrowKey(Blame::Util::ArrowKey arrowKey) override {}

        std::string getCurrentBorderColour() {
            switch (this->state) {
                case Blame::Util::State::NORMAL:
                    return this->colour_border;

                case Blame::Util::State::FOCUSED:
                    return this->colour_focus_border;

                case Blame::Util::State::DISABLED:
                    return this->colour_disable_border;
            }
        }

        void place(int x, int y, int width, int height) {
            this->column = x;
            this->row = y;
            this->width = width;
            this->height = height;

            this->redraw();
        }
        // void placeRemove();

        // void pack();
        // void packRemove();

        // void grid(int row, int column);
        // void gridRemove();

        int column;
        int row;
        int width;
        int height;

        Blame::Util::ClientArea client_area;

        bool resizable;

        std::ostringstream widget_stream;

    protected:
        Blame::Console *console;
        std::optional<Blame::Widgets::Widget*> parent;

        // int padding_top;
        // int padding_left;
        // int padding_right;
        // int padding_bottom;

        // int internal_padding_top;
        // int internal_padding_left;
        // int internal_padding_right;
        // int internal_padding_bottom;

        std::string colour_border;
        std::string colour_background;
        std::string colour_text;

        std::string colour_focus_border;
        std::string colour_focus_background;
        std::string colour_focus_text;

        std::string colour_disable_border;
        std::string colour_disable_background;
        std::string colour_disable_text;

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