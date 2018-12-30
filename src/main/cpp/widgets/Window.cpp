#include "Window.hpp"

#include <iostream>
#include "../util/EscapeCodes.hpp"

Blame::Widgets::Window::Window(Console *console, std::string title_text, int column, int row, int width, int height) : Widget(console, nullptr, column, row, width, height) {
    this->console = console;
    this->title_text = title_text;
    this->column = column;
    this->row = row;
    this->width = width;
    this->height = height;

    this->colour_border = Blame::Util::EscapeCodes::foregroundCyan();
    this->colour_background = Blame::Util::EscapeCodes::backgroundWhite();
    this->colour_text = Blame::Util::EscapeCodes::foregroundBlack();

    this->symbol_top_left = "╔";
    this->symbol_top_middle = "═";
    this->symbol_top_right = "╗";
    this->symbol_middle_left = "║";
    // this->symbol_middle_fill = "░";
    this->symbol_middle_fill = "█";
    this->symbol_middle_right = "║";
    this->symbol_bottom_left = "╚";
    this->symbol_bottom_middle = "═";
    this->symbol_bottom_right = "╝";

    this->symbol_title_intersect_left = "╠";
    this->symbol_title_intersect_right = "╣";
}

void Blame::Widgets::Window::redraw() {
    this->console->moveCaret(this->column, this->row);

    std::cout << this->colour_border;
    for (int h = 0; h < 3; h++) {
        this->console->moveCaret(this->column, this->row + h);
        std::cout << this->colour_background;
        for (int w = 0; w < this->width; w++) {
            // Top Left
            if (w == 0 && h == 0) {
                std::cout << this->colour_border;
                std::cout << this->symbol_top_left;
            }
            // Middle Left
            else if (w == 0 && h > 0 && h < this->height - 1) {
                std::cout << this->colour_border;
                std::cout << this->symbol_middle_left;
            }

            // Top Middle
            if (h == 0) {
                std::cout << this->colour_border;
                std::cout << this->symbol_top_middle;
            }
            // Middle Fill
            else {
                if (w == 1) {
                    std::cout << this->colour_text;
                    std::cout << this->title_text;
                }
                else if (w == 0 || w > this->title_text.length()) {
                    std::cout << Blame::Util::EscapeCodes::foregroundWhite();
                    std::cout << this->symbol_middle_fill;
                }
            }

            // Top Right
            if (w == this->width - 1 && h == 0) {
                std::cout << this->colour_border;
                std::cout << this->symbol_top_right;
            }
                // Middle Right
            else if (w == this->width - 1 && h > 0 && h < this->height - 1) {
                std::cout << this->colour_border;
                std::cout << this->symbol_middle_right;
            }
        }
        std::cout << Blame::Util::EscapeCodes::reset();
        std::cout << std::endl;
    }

    this->symbol_top_left = this->symbol_title_intersect_left;
    this->symbol_top_right = this->symbol_title_intersect_right;

    this->row += 2;
    Widget::redraw();

    this->symbol_top_left = "╔";
    this->symbol_top_right = "╗";
}

void Blame::Widgets::Window::arrowKey(Blame::Util::ArrowKey arrowKey) {
    switch (arrowKey) {
        case Blame::Util::ArrowKey::UP:
            this->row -= 3;
            break;

        case Blame::Util::ArrowKey::DOWN:
            this->row--;
            break;

        case Blame::Util::ArrowKey::LEFT:
            this->row -= 2;
            this->column--;
            break;

        case Blame::Util::ArrowKey::RIGHT:
            this->row -= 2;
            this->column++;
            break;
    }

    // TODO: Have the console clear itself and redraw everything
    this->redraw();
}
