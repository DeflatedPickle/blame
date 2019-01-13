#include <Console.hpp>

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <algorithm>
#include <chrono>
#include <thread>

#include <widgets/Widget.hpp>

// TODO: Add signals for console events
Blame::Console::Console() {
    this->clear();
    this->moveCaret(std::cout, 0, 0);
    std::cout << Blame::Util::EscapeCodes::caretOff();

    this->buffer_list.push_back(&front_buffer);
    this->buffer_list.push_back(&back_buffer);

    this->exit.store(false);
    this->has_flipped.store(true);

    struct winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    this->width = size.ws_col;
    this->height = size.ws_row;

    // Creates a row of empty cells for the height and width of the terminal
    for (auto i = 0; i < this->height; i++) {
        std::vector<std::string> vec;

        for (auto j = 0; j < this->width + 1; j++) {
            vec.emplace_back("");
        }

        this->raw_grid.push_back(vec);
        this->screen_grid.push_back(vec);
    }

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

Blame::Console::~Console() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    term.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void Blame::Console::mainLoop() {
    char first;
    char second;
    char third;

    bool find_second_third;

    this->focused_widget = this->focus_order[0];
    this->focused_widget->focus();

    // std::thread draw_thread(&Blame::Console::drawLoop, this);

    // this->drawBackground();

    while (!this->exit.load()) {
        find_second_third = true;
        std::cout.flush();

        // std::cin >> first;

        first = (char) std::cin.get();

        // TODO: Change to the Escape key
        if (first == 'q') {
            this->clear();
            this->quit();
        }

        // Tab
        if (first == 9) {
            this->incrementFocus();
            find_second_third = false;
        }

        // TODO: Change to the Enter key
        if (first == 'e') {
            auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
            focused_widget->activate();
            find_second_third = false;
        }

        if (first != 27) {
            auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
            focused_widget->text(std::string(1, first));
            find_second_third = false;
        }

        if (find_second_third) {
            std::cin >> second;
            std::cin >> third;
        }

        if (first == 27 && second == 91) {
            if (third == 65) {
                // std::cout << "UP";
                auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
                focused_widget->move(Blame::Util::Direction::UP);
            }
            else if (third == 66) {
                // std::cout << "DOWN";
                auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
                focused_widget->move(Blame::Util::Direction::DOWN);
            }
            else if (third == 67) {
                // std::cout << "RIGHT";
                auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
                focused_widget->move(Blame::Util::Direction::RIGHT);
            }
            else if (third == 68) {
                // std::cout << "LEFT";
                auto focused_widget = dynamic_cast<Blame::Widgets::Widget *>(this->focused_widget);
                focused_widget->move(Blame::Util::Direction::LEFT);
            }
        }
    }
}

void Blame::Console::drawLoop() {
    std::chrono::milliseconds current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds start_time = current_time;
    int frame_count = 0;

    while (!this->exit.load()) {
        frame_count++;
        current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        // this->setTitle("Current Time: " + std::to_string(current_time.count()) + " Start Time:" + std::to_string(start_time.count()) + " Final: " + std::to_string(current_time.count() - start_time.count()));
        if (current_time.count() - start_time.count() > 0.25f) {
            frame_count = 0;

            start_time = current_time;

            // this->setTitle("--------------------------------");
            if (this->has_flipped.load()) {
                this->has_flipped.exchange(false);

                if (this->buffer_list[this->current_buffer]->rdbuf() != std::cout.rdbuf()) {
                    this->redraw();
                }
            }
        }
    }
}

void Blame::Console::clear() {
    std::cout << Blame::Util::EscapeCodes::reset();
    std::cout << "\033c";
}

void Blame::Console::redraw() {
    // TODO: Only redraw the cells that have been changed, don't clear the whole thing
    // this->clear();

    // this->drawBackground();

    // TODO: Maybe add a check for if they need to be redrawn?
    for (auto widget : this->widget_list) {
        // The widgets are added as listeners, since the Widget class is incomplete at the time of headers
        // meaning they can't be used for the typing of the list, so we have to cast them to widgets...
        // which they might not be
        auto new_widget = dynamic_cast<Blame::Widgets::Widget *>(widget);

        if (new_widget->is_redrawn.load()) {
            new_widget->redraw();

            if (!new_widget->children.empty()) {
                for (auto child : new_widget->children) {
                    child->redraw();
                }
            }
        }
    }

    // TODO: Group cells into packets
    // auto redraw_count = 0;
    for (auto y = 0; y < this->raw_grid.size(); y++) {
        for (auto x = 0; x < this->raw_grid[y].size(); x++) {
            if (x == this->raw_grid[y].size()) {
                if (y != this->raw_grid.size()) {
                    *this->buffer_list[!this->current_buffer] << std::endl;
                }
            }

            // TODO: Remove leftward caret movements
            this->moveCaret(*this->buffer_list[!this->current_buffer], x, y);

            if (x > 0 && y > 0 && this->raw_grid[y][x].empty()) {
                *this->buffer_list[!this->current_buffer] << "░" << Blame::Util::EscapeCodes::reset();
            }

            if (this->raw_grid[y][x] != this->screen_grid[y][x]) {
                this->screen_grid[y][x] = this->raw_grid[y][x];

                // redraw_count++;
                // this->setTitle("Redrawn: " + std::to_string(redraw_count) + " Cells, Out Of: " + std::to_string(this->raw_grid.size() * this->raw_grid[0].size()) + " Cells");
            }
            else {
                // Shows which cells were redrawn
                // *this->buffer_list[!this->current_buffer] << "@" << Blame::Util::EscapeCodes::reset();
                continue;
            }

            *this->buffer_list[!this->current_buffer] << Blame::Util::EscapeCodes::reset() << this->screen_grid[y][x] << Blame::Util::EscapeCodes::reset();
        }
    }

    this->flipBuffers();
}

void Blame::Console::setTitle(std::string str) {
    std::cout << "\033]2;" << str.c_str() << "\007";
}

void Blame::Console::moveCaret(std::ostream &stream, int column, int row) {
    stream << "\033[" << row << ";" << column << "H";
}
