#pragma once

#include <functional>
#include "Widget.hpp"

namespace Blame::Widgets {
    class Button : public Blame::Widgets::Widget {
    public:
        Button(Blame::Console *console, Blame::Widgets::Widget *parent, std::string text, std::function<void()> command);

        void redraw() override;

        void activate() override {
            this->command();
        }

        std::string text;
        std::function<void()> command;
    };
}
