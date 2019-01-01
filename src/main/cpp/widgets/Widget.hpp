#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include "../Console.hpp"
#include "Listener.hpp"
#include "../util/EscapeCodes.hpp"
#include "../util/State.hpp"
#include "../styles/Style.hpp"

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
                    return this->style->colours->border;

                case Blame::Util::State::FOCUSED:
                    return this->style->colours->focus_border;

                case Blame::Util::State::DISABLED:
                    return this->style->colours->disable_border;
            }
        }

        void place(int x, int y, int width, int height) {
            this->column = x;
            this->row = y;
            this->width = width;
            this->height = height;
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

        std::atomic_bool is_redrawn;

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

        Blame::Styles::Style *style;
    };
}