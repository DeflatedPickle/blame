#pragma once

#include <vector>
#include <string>
#include "widgets/Listener.hpp"
#include "util/ClientArea.hpp"

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

        Blame::Util::ClientArea client_area;

        std::vector<Blame::Widgets::Listener *> widget_list;
        std::vector<Blame::Widgets::Listener *> focus_order;
        Blame::Widgets::Listener *focused_widget;

    protected:
        // std::string colour_background;
    };
}