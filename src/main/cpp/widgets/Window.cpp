#include "Window.hpp"

#include <iostream>
#include "../util/EscapeCodes.hpp"
#include "../styles/StyleWindow.hpp"

Blame::Widgets::Window::Window(Console *console, std::string title_text) : Widget(console, nullptr) {
    this->console = console;
    this->title_text = title_text;

    this->symbol_title_intersect_left = "╠";
    this->symbol_title_intersect_right = "╣";

    this->style = new Blame::Styles::StyleWindow();
}

// FIXME: Draws the line under the title twice
void Blame::Widgets::Window::redraw() {
    this->is_redrawn.exchange(false);

    this->console->moveCaret(this->widget_stream, this->column, this->row);
    // Account for the title height
    this->row -= 2;

    this->widget_stream << this->style->colours->border;
    for (int h = 0; h < 3; h++) {
        this->console->moveCaret(this->widget_stream, this->column, this->row + h);
        this->widget_stream << this->style->colours->background;
        for (int w = 0; w < this->width; w++) {
            // Top Left
            if (w == 0 && h == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_left;
            }
            // Middle Left
            else if (w == 0 && h > 0 && h < this->height - 1) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->middle_left;
            }

            // Top Middle
            if (h == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_middle;
            }
            // Middle Fill
            else {
                if (w == 1) {
                    this->widget_stream << this->style->colours->text;
                    this->widget_stream << this->title_text;
                }
                else if (w == 0 || w > this->title_text.length()) {
                    this->widget_stream << Blame::Util::EscapeCodes::reset();
                    this->widget_stream << this->style->colours->background;
                    this->widget_stream << this->style->symbols->middle_fill;
                }
            }

            // Top Right
            if (w == this->width - 1 && h == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_right;
            }
                // Middle Right
            else if (w == this->width - 1 && h > 0 && h < this->height - 1) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->middle_right;
            }
        }
        this->widget_stream << Blame::Util::EscapeCodes::reset();
        this->widget_stream << std::endl;
    }

    this->style->symbols->top_left = this->symbol_title_intersect_left;
    this->style->symbols->top_right = this->symbol_title_intersect_right;

    this->row += 2;
    Widget::redraw();

    this->style->symbols->top_left = "╔";
    this->style->symbols->top_right = "╗";

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Window::arrowKey(Blame::Util::ArrowKey arrowKey) {
    if (this != this->console->focused_widget)
        return;

    switch (arrowKey) {
        case Blame::Util::ArrowKey::UP:
            if (this->row - 3 > console->client_area.top) {
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
}
