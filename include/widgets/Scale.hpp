#pragma once

#include <functional>

#include <util/Orientation.hpp>
#include <widgets/Widget.hpp>

namespace Blame::Widgets {
    class Scale : public Blame::Widgets::Widget {
    public:
        Scale(Blame::Console *console, Blame::Widgets::Widget *parent, Blame::Util::Orientation orientation, std::function<void()> command);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;

        void activate() override {}

        Blame::Util::Orientation orientation;
        std::function<void()> command;

        float min;
        float current;
        float max;

    protected:
        int handle_min;
        int handle_current;
        int handle_max;

        std::string symbol_handle;

        std::string colour_handle;
    };
}
