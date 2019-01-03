#include "Widget.hpp"

#include <iostream>
#include <optional>
#include "../util/EscapeCodes.hpp"

Blame::Widgets::Widget::Widget(Blame::Console *console, Blame::Widgets::Widget *parent) {
    this->console = console;
    this->parent = parent;

    if (this->parent != nullptr) {
        this->parent->children.push_back(this);
    }
    else {
        this->console->widget_list.push_back(this);
    }

    this->console->focus_order.push_back(this);

    this->is_redrawn.store(true);

    this->updateClientArea();
}

void Blame::Widgets::Widget::redraw() {
    this->updateClientArea();
    this->is_redrawn.exchange(false);

    this->widget_stream << Blame::Util::EscapeCodes::reset();
    this->console->moveCaret(this->widget_stream, this->column, this->row);

    for (int y = 0; y < this->height; y++) {
        this->console->moveCaret(this->widget_stream, this->column, this->row + y);

        for (int x = 0; x < this->width; x++) {
            this->widget_stream << Blame::Util::EscapeCodes::reset();

            // Top Left
            if (x == 0 && y == 0) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->top_left;
            }
                // Middle Left
            else if (x == 0 && y > 0 && y < this->height - 1) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->middle_left;
            }
                // Bottom Left
            else if (x == 0 && y == this->height - 1) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->bottom_left;
            }

            // Top Middle
            if (y == 0) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->top_middle;
            }
            // Bottom Middle
            else if (y == this->height - 1) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->bottom_middle;
            }
            // Middle Fill
            else {
                this->widget_stream << Blame::Util::EscapeCodes::reset();
                this->widget_stream << this->getCurrentColour(this->style->colours->background_content);
                this->widget_stream << this->style->symbols->middle_fill;
                this->widget_stream << Blame::Util::EscapeCodes::reset();
            }

            // Top Right
            if (x == this->width - 1 && y == 0) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->top_right;
            }
            // Middle Right
            else if (x == this->width - 1 && y > 0 && y < this->height - 1) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->middle_right;
            }
            // Bottom Right
            else if (x == this->width - 1 && y == this->height - 1) {
                this->widget_stream << this->getCurrentColour(this->style->colours->border);
                this->widget_stream << this->getCurrentColour(this->style->colours->background_border);
                this->widget_stream << this->style->symbols->bottom_right;
            }
        }
        this->widget_stream << Blame::Util::EscapeCodes::reset();
    }

    this->widget_stream << Blame::Util::EscapeCodes::reset();
    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

    this->is_redrawn.exchange(true);
}
