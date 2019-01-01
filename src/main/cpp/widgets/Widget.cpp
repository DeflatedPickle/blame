#include "Widget.hpp"

#include <iostream>
#include <optional>
#include "../util/EscapeCodes.hpp"

Blame::Widgets::Widget::Widget(Blame::Console *console, std::optional<Blame::Widgets::Widget*> parent) {
    this->console = console;
    this->parent = parent;

    this->console->widget_list.push_back(this);
    this->console->focus_order.push_back(this);

    this->is_redrawn.store(true);
}

void Blame::Widgets::Widget::redraw() {
    this->is_redrawn.exchange(false);

    this->console->moveCaret(this->widget_stream, this->column, this->row);

    for (int h = 0; h < this->height; h++) {
        this->console->moveCaret(this->widget_stream, this->column, this->row + h);

        for (int w = 0; w < this->width; w++) {
            // Top Left
            if (w == 0 && h == 0) {
                this->setColours();
                this->widget_stream << this->style->symbols->top_left;
            }
            // Middle Left
            else if (w == 0 && h > 0 && h < this->height - 1) {
                this->setColours();
                this->widget_stream << this->style->symbols->middle_left;
            }
            // Bottom Left
            else if (w == 0 && h == this->height - 1) {
                this->setColours();
                this->widget_stream << this->style->symbols->bottom_left;
            }

            // Top Middle
            if (h == 0) {
                this->setColours();
                this->widget_stream << this->style->symbols->top_middle;
            }
            // Bottom Middle
            else if (h == this->height - 1) {
                this->setColours();
                this->widget_stream << this->style->symbols->bottom_middle;
            }
            // Middle Fill
            else {
                this->widget_stream << Blame::Util::EscapeCodes::reset();
                this->widget_stream << this->style->colours->background;
                this->widget_stream << this->style->symbols->middle_fill;
            }

            // Top Right
            if (w == this->width - 1 && h == 0) {
                this->setColours();
                this->widget_stream << this->style->symbols->top_right;
            }
            // Middle Right
            else if (w == this->width - 1 && h > 0 && h < this->height - 1) {
                this->setColours();
                this->widget_stream << this->style->symbols->middle_right;
            }
            // Bottom Right
            else if (w == this->width - 1 && h == this->height - 1) {
                this->setColours();
                this->widget_stream << this->style->symbols->bottom_right;
            }
        }
        this->widget_stream << Blame::Util::EscapeCodes::reset();
        this->widget_stream << std::endl;
    }

    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Widget::setColours() {
    widget_stream << this->getCurrentBorderColour();
    widget_stream << this->style->colours->background;
}
