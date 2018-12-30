#include "Window.hpp"

#include <iostream>
#include "../util/EscapeCodes.hpp"

Blame::Widgets::Window::Window(Console *console, std::string title_text) : Widget(console, nullptr) {
    this->console = console;
    this->title_text = title_text;

    this->colour_border = Blame::Util::EscapeCodes::foregroundCyan();
    this->colour_background = Blame::Util::EscapeCodes::backgroundWhite();
    this->colour_text = Blame::Util::EscapeCodes::foregroundBlack();

    this->colour_focus_border = Blame::Util::EscapeCodes::foregroundGreen();

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
                std::cout << this->getCurrentBorderColour();
                std::cout << this->symbol_top_left;
            }
            // Middle Left
            else if (w == 0 && h > 0 && h < this->height - 1) {
                std::cout << this->getCurrentBorderColour();
                std::cout << this->symbol_middle_left;
            }

            // Top Middle
            if (h == 0) {
                std::cout << this->getCurrentBorderColour();
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
                std::cout << this->getCurrentBorderColour();
                std::cout << this->symbol_top_right;
            }
                // Middle Right
            else if (w == this->width - 1 && h > 0 && h < this->height - 1) {
                std::cout << this->getCurrentBorderColour();
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
    // Account for the title height
    this->row -= 2;

    if (this != this->console->focused_widget)
        return;

    switch (arrowKey) {
        case Blame::Util::ArrowKey::UP:
            if (this->row - 1 > console->client_area.top) {
                this->row -= 1;
            }
            break;

        case Blame::Util::ArrowKey::DOWN:
            if (this->row + 1 + this->height < console->client_area.bottom) {
                this->row++;
            }
            break;

        case Blame::Util::ArrowKey::LEFT:
            if (this->column - 1 > console->client_area.left) {
                this->column--;
            }
            break;

        case Blame::Util::ArrowKey::RIGHT:
            if (this->column + 1 + this->width < console->client_area.right) {
                this->column++;
            }
            break;
    }

    console->redraw();
}
