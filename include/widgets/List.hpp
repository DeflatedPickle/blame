#pragma once

#include <functional>
#include <vector>

#include <widgets/Widget.hpp>
#include <widgets/Scrollable.hpp>

namespace Blame::Widgets {
    class List : public Blame::Widgets::Scrollable {
    public:
        List(Blame::Console *console, Blame::Widgets::Widget *parent, std::vector<std::string> items, std::function<void()> command);

        void redraw() override;

        void move(Blame::Util::Direction direction) override {
            if (direction == Blame::Util::Direction::UP) {
                if (this->selection >= 1) {
                    this->selection--;
                }
            } else if (direction == Blame::Util::Direction::DOWN) {
                if (this->selection < (this->content.size() - 1)) {
                    this->selection++;
                }
            }

            Widget::move(direction);
        }

        void activate() override {
            this->command();

            Widget::activate();
        }

        std::function<void()> command;

        int selection;
    };
}

