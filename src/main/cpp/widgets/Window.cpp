#include "Window.hpp"
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

    this->symbol_top_left = "╔";
    this->symbol_top_middle = "═";
    this->symbol_top_right = "╗";
    this->symbol_middle_left = "║";
    this->symbol_middle_fill = "░";
    this->symbol_middle_right = "║";
    this->symbol_bottom_left = "╚";
    this->symbol_bottom_middle = "═";
    this->symbol_bottom_right = "╝";
}

void Blame::Widgets::Window::redraw() {
    Widget::redraw();
}
