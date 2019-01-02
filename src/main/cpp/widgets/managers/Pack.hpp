#pragma once

#include "Manager.hpp"
#include "../../util/Direction.hpp"

namespace Blame::Widgets {
    class Widget;
}

namespace Blame::Widgets::Managers {
    class Pack : public Blame::Widgets::Managers::Manager {
    public:
        Blame::Util::Direction direction;

        int next_x;
        int next_y;

        std::vector<Blame::Widgets::Widget *> widgets;
    };
}