#include "Window.hpp"

#include <iostream>
#include "../util/EscapeCodes.hpp"
#include "../styles/StyleWindow.hpp"

Blame::Widgets::Window::Window(Blame::Console *console, std::string title_text) : Widget(console, nullptr) {
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
    for (int y = 0; y < 3; y++) {
        this->console->moveCaret(this->widget_stream, this->column, this->row + y);
        this->widget_stream << this->style->colours->background;
        for (int x = 0; x < this->width; x++) {
            // Top Left
            if (x == 0 && y == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_left;
            }
            // Middle Left
            else if (x == 0 && y > 0 && y < this->height - 1) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->middle_left;
            }

            // Top Middle
            if (y == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_middle;
            }
            // Middle Fill
            else {
                if (x == 1) {
                    this->widget_stream << Blame::Util::EscapeCodes::reset();
                    this->widget_stream << this->style->colours->background;
                    this->widget_stream << this->style->colours->text;
                    this->widget_stream << this->title_text;
                }
                else if (x == 0 || x > this->title_text.length()) {
                    this->widget_stream << Blame::Util::EscapeCodes::reset();
                    this->widget_stream << this->style->colours->background;
                    this->widget_stream << this->style->symbols->middle_fill;
                }
            }

            // Top Right
            if (x == this->width - 1 && y == 0) {
                this->widget_stream << this->getCurrentBorderColour();
                this->widget_stream << this->style->symbols->top_right;
            }
                // Middle Right
            else if (x == this->width - 1 && y > 0 && y < this->height - 1) {
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

void Blame::Widgets::Window::move(Blame::Util::Direction direction) {
    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->row - 3 > console->client_area.top) {
                this->row--;

                for (auto child : this->children) {
                    child->row--;
                }
            }
            break;

        case Blame::Util::Direction::DOWN:
            if (this->row + 1 + this->height < console->client_area.bottom) {
                this->row++;

                for (auto child : this->children) {
                    child->row++;
                }
            }
            break;

        case Blame::Util::Direction::LEFT:
            if (this->column - 1 > console->client_area.left) {
                this->column--;

                for (auto child : this->children) {
                    child->column--;
                }
            }
            break;

        case Blame::Util::Direction::RIGHT:
            if (this->column + 1 + this->width < console->client_area.right) {
                this->column++;

                for (auto child : this->children) {
                    child->column++;
                }
            }
            break;
    }

    Widget::move(direction);
}
