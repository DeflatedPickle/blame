#pragma once

#include <vector>
#include "widgets/Listener.hpp"

namespace Blame {
    class Console {
    public:
        Console();

        void mainloop();

        void clear();

        void redraw();

        void moveCaret(int column, int row);

        int width;
        int height;

        std::vector<Blame::Widgets::Listener *> widgetList;

    protected:
        // std::string colour_background;
    };
}