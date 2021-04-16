#pragma once

#include <functional>

#include <util/Orientation.hpp>
#include <widgets/Scrollable.hpp>
#include <widgets/Widget.hpp>

namespace Blame::Widgets {
    class Scroll : public Blame::Widgets::Widget {
    public:
        Scroll(Blame::Console *console, Blame::Widgets::Widget *parent, Blame::Util::Orientation orientation, Blame::Widgets::Scrollable *associated_widget);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;

        void activate() override {}

        Blame::Util::Orientation orientation;
/*        std::vector<Blame::Widgets::Widget *> widgets;*/
        Scrollable *enclosed_widget;

        int min = 0;
        int current = 0;
        int max = 0;

        int handle_min;
        int handle_current;
        int handle_max;

        int handle_size = 1;

    protected:
        std::string symbol_handle;

        std::string colour_handle;
    };
}
