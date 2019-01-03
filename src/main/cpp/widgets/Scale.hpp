#pragma once

#include "Widget.hpp"
#include "../util/Orientation.hpp"

namespace Blame::Widgets {
    class Scale : public Blame::Widgets::Widget {
    public:
        Scale(Blame::Console *console, Blame::Widgets::Widget *parent, Blame::Util::Orientation orientation);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;

        Blame::Util::Orientation orientation;

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
