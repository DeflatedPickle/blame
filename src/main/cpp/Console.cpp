#include "Console.hpp"

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <algorithm>
#include "util/EscapeCodes.hpp"
#include "util/ArrowKey.hpp"
#include "widgets/Widget.hpp"

// TODO: Add signals for console events
Blame::Console::Console() {
    this->clear();
    this->moveCaret(0, 0);

    struct winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    this->width = size.ws_col;
    this->height = size.ws_row;

    this->client_area.left = 0;
    this->client_area.top = 0;
    this->client_area.right = this->width;
    this->client_area.bottom = this->height;

    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void Blame::Console::mainloop() {
    char first;
    char second;
    char third;

    bool find_second_third;

    this->focused_widget = this->focus_order[0];
    this->focused_widget->focus();

    while (true) {
        find_second_third = true;
        std::cout.flush();

        std::cin >> first;

        if (first == 'q') {
            std::cout << std::endl;

            // Perform clean up on all widgets
            for (auto widget : this->widget_list) {
                widget->quit();
            }

            break;
        }

        if (first == 'f') {
            auto pos = distance(focus_order.begin(), find(focus_order.begin(), focus_order.end(), this->focused_widget));

            this->focused_widget->unfocus();
            if (pos + 1 >= this->focus_order.size()) {
                this->focus_order[0]->focus();
            }
            else {
                this->focus_order[pos + 1]->focus();
            }

            find_second_third = false;
        }

        if (find_second_third) {
            std::cin >> second;
            std::cin >> third;
        }

        if (first == 27 && second == 91) {
            if (third == 65) {
                // std::cout << "UP";
                for (auto widget : this->widget_list) {
                    widget->arrowKey(Blame::Util::ArrowKey::UP);
                }
            }
            else if (third == 66) {
                // std::cout << "DOWN";
                for (auto widget : this->widget_list) {
                    widget->arrowKey(Blame::Util::ArrowKey::DOWN);
                }
            }
            else if (third == 67) {
                // std::cout << "RIGHT";
                for (auto widget : this->widget_list) {
                    widget->arrowKey(Blame::Util::ArrowKey::RIGHT);
                }
            }
            else if (third == 68) {
                // std::cout << "LEFT";
                for (auto widget : this->widget_list) {
                    widget->arrowKey(Blame::Util::ArrowKey::LEFT);
                }
            }
        }
    }
}

void Blame::Console::clear() {
    std::cout << Blame::Util::EscapeCodes::reset();
    printf("\033c");
}

void Blame::Console::redraw() {
    // TODO: Only redraw the cells that have been changed, don't clear the whole thing
    this->clear();

    this->moveCaret(0, 0);

    // TODO: Maybe add a check for if they need to be redrawn?
    for (auto widget : this->widget_list) {
        // The widgets are added as listeners, since the Widget class is incomplete at the time of headers
        // meaning they can't be used for the typing of the list, so we have to cast them to widgets...
        // which they might not be
        auto new_widget = dynamic_cast<Blame::Widgets::Widget *>(widget);
        new_widget->redraw();
    }
}

void Blame::Console::setTitle(std::string str) {
    printf("\033]2;%s\007", str.c_str());
}

void Blame::Console::moveCaret(int column, int row) {
    printf("\033[%d;%dH", row, column);
}
