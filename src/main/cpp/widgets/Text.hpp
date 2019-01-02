#pragma once

#include "Widget.hpp"

namespace Blame::Widgets {
    class Text : public Blame::Widgets::Widget {
    public:
        Text(Blame::Console *console, Blame::Widgets::Widget *parent);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;
        void text(std::string text) override;

        int caret_x;
        int caret_y;

        std::string content;

    protected:
        std::string symbol_caret;

        std::string colour_caret;
    };
}
