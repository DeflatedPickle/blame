#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <atomic>
#include <iostream>
#include <thread>
#include <algorithm>
#include "widgets/Listener.hpp"
#include "util/ClientArea.hpp"
#include "util/EscapeCodes.hpp"

namespace Blame {
    class Console {
    public:
        Console();

        void mainLoop();
        void drawLoop();

        void clear();

        void redraw();
        void drawBackground() {
            this->moveCaret(std::cout, 0, 0);

            for (int y = 0; y < this->height - 1; y++) {
                for (int x = 0; x < this->width; x++) {
                    *this->buffer_list[this->current_buffer] << "░";
                }
            }

            this->flipBuffers();
        }

        void setTitle(std::string str);

        void moveCaret(std::ostream& stream, int column, int row);

        void quit() {
            this->exit.store(true);
            std::cout << std::endl;

            // Perform clean up on all widgets
            for (auto widget : this->widget_list) {
                widget->quit();
            }

            std::exit(0);
        }

        void incrementFocus() {
            auto pos = std::distance(focus_order.begin(),
                                std::find(focus_order.begin(), focus_order.end(), this->focused_widget));

            this->focused_widget->unfocus();
            if (pos + 1 >= this->focus_order.size()) {
                this->focus_order[0]->focus();
            }
            else {
                this->focus_order[pos + 1]->focus();
            }
        }

        void flipBuffers() {
            this->has_flipped.exchange(true);

            switch (this->current_buffer) {
                case 0:
                    std::cout << back_buffer.str();
                    // Clear the buffer
                    back_buffer.str(std::string());
                    this->current_buffer = 1;
                    break;

                case 1:
                    std::cout << front_buffer.str();
                    // Clear the buffer
                    front_buffer.str(std::string());
                    this->current_buffer = 0;
                    break;

                default:
                    break;
            }

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