#pragma once

#include <string>
#include "Widget.hpp"

namespace Blame::Widgets {
    class Window : public Widget {
    public:
        Window(Blame::Console *console, std::string title_text);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;

        std::string title_text;

    protected:
        std::string symbol_title_intersect_left;
        std::string symbol_title_intersect_right;

        std::string colour_background_title;

        std::string symbol_minimize;
        std::string symbol_maximize;
        std::string symbol_restore;
        std::string symbol_close;
    };
}