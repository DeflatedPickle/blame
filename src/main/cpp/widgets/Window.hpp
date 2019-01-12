#pragma once

#include <string>
#include <util/StateWindow.hpp>
#include "Widget.hpp"

namespace Blame::Widgets {
    class Window : public Blame::Widgets::Widget {
    public:
        Window(Blame::Console *console, std::string title_text);

        void redraw() override;

        void move(Blame::Util::Direction direction) override;

        void activate() override {}

        // void restore();
        // void minimize();
        // void maximize();
        void fullscreen() {
            this->old_width = this->width;
            this->old_height = this->height;

            this->state_window = Blame::Util::StateWindow::FULLSCREEN;

            this->width = this->console->width - 2;
            this->height = this->console->height - 1;
        }
        // void close();

        std::string title_text;

        Blame::Util::StateWindow state_window = Blame::Util::StateWindow::RESTORED;

    protected:
        std::string symbol_title_intersect_left;
        std::string symbol_title_intersect_right;

        std::string colour_background_title;

        std::string symbol_minimize;
        std::string symbol_maximize;
        std::string symbol_restore;
        std::string symbol_close;

    private:
        int old_width;
        int old_height;
    };
}