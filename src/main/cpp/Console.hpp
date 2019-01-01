#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <atomic>
#include <iostream>
#include <thread>
#include "widgets/Listener.hpp"
#include "util/ClientArea.hpp"

namespace Blame {
    class Console {
    public:
        Console();

        void mainLoop();
        void drawLoop();
        void bufferLoop();

        void clear();

        void redraw();

        void setTitle(std::string str);

        void moveCaret(std::ostream& stream, int column, int row);

        void flipBuffers() {
            this->has_flipped.exchange(true);

            switch (this->current_buffer) {
                case 0:
                    std::cout << front_buffer.str();
                    front_buffer.str(std::string());
                    this->current_buffer = 1;
                    break;

                case 1:
                    std::cout << back_buffer.str();
                    back_buffer.str(std::string());
                    this->current_buffer = 0;
                    break;

                default:
                    break;
            }

            // Clear the hidden buffer
            // this->buffer_list[!this->current_buffer]->str(std::string());

            // this->setTitle(std::to_string(this->current_buffer));
        }

        int width;
        int height;

        Blame::Util::ClientArea client_area;

        std::vector<Blame::Widgets::Listener *> widget_list;
        std::vector<Blame::Widgets::Listener *> focus_order;
        Blame::Widgets::Listener *focused_widget;

        std::ostringstream front_buffer;
        std::ostringstream back_buffer;
        std::vector<std::ostringstream *> buffer_list;
        int current_buffer;

        std::atomic_bool has_flipped;

    protected:
        // std::string colour_background;
        std::atomic_bool exit;
    };
}