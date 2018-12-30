#include "Console.hpp"

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "util/EscapeCodes.hpp"
#include "util/ArrowKey.hpp"

// TODO: Add signals for console events
Blame::Console::Console() {
    this->clear();
    this->moveCaret(0, 0);

    struct winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    this->width = size.ws_col;
    this->height = size.ws_row;

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

    while (true) {
        std::cout.flush();

        std::cin >> first;

        if (first == 'q') {
            std::cout << std::endl;

            // Perform clean up on all widgets
            for (auto widget : this->widgetList) {
                widget->quit();
            }

            break;
        }

        std::cin >> second;
        std::cin >> third;

        if (first == 27 && second == 91) {
            if (third == 65) {
                // std::cout << "UP";
                for (auto widget : this->widgetList) {
                    widget->arrowKey(Blame::Util::ArrowKey::UP);
                }
            }
            else if (third == 66) {
                // std::cout << "DOWN";
                for (auto widget : this->widgetList) {
                    widget->arrowKey(Blame::Util::ArrowKey::DOWN);
                }
            }
            else if (third == 67) {
                // std::cout << "RIGHT";
                for (auto widget : this->widgetList) {
                    widget->arrowKey(Blame::Util::ArrowKey::RIGHT);
                }
            }
            else if (third == 68) {
                // std::cout << "LEFT";
                for (auto widget : this->widgetList) {
                    widget->arrowKey(Blame::Util::ArrowKey::LEFT);
                }
            }
        }
    }
}

void Blame::Console::moveCaret(int column, int row) {
    printf("\033[%d;%dH", row, column);
}

void Blame::Console::clear() {
    std::cout << Blame::Util::EscapeCodes::reset();
    printf("\033c");
}
