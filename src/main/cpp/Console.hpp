#pragma once

#include <vector>
#include <string>
#include "widgets/Listener.hpp"

namespace Blame {
    class Console {
    public:
        Console();

        void mainloop();

        void clear();

        void redraw();

        void setTitle(std::string str);

        void moveCaret(int column, int row);

        int width;
        int height;

        int client_area_left;
        int client_area_right;
        int client_area_top;
        int client_area_bottom;

        std::vector<Blame::Widgets::Listener *> widgetList;

    protected:
        // std::string colour_background;
    };
}