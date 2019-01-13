#include "Widget.hpp"

#include <iostream>

Blame::Widgets::Widget::Widget(Blame::Console *console, Blame::Widgets::Widget *parent) {
    this->console = console;
    this->parent = parent;

    // Should Be Handled by Parent or Console:
    // Valgrind warning
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

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width + 1; x++) {
            // Top Left
            if (x == 0 && y == 0) {
                this->console->raw_grid[this->row + y + 1][this->column + x] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.top_left;
            }
            // Middle Left
            else if (x == 0 && y > 0 && y < this->height - 1) {
                this->console->raw_grid[this->row + y + 1][this->column + x] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.middle_left;
            }
            // Bottom Left
            else if (x == 0 && y == this->height - 1) {
                this->console->raw_grid[this->row + y + 1][this->column + x] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.bottom_left;
            }

            // Top Middle
            if (y == 0) {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.top_middle;
            }
            // Bottom Middle
            else if (y == this->height - 1) {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.bottom_middle;
            }
            // Middle Fill
            else {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.background_content)
                        + this->style.symbols.middle_fill;
            }

            // Top Right
            if (x == this->width && y == 0) {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.top_right;
            }
            // Middle Right
            else if (x == this->width && y > 0 && y < this->height - 1) {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.middle_right;
            }
            // Bottom Right
            else if (x == this->width && y == this->height - 1) {
                this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                        this->getCurrentColour(this->style.colours.border)
                        + this->getCurrentColour(this->style.colours.background_border)
                        + this->style.symbols.bottom_right;
            }
        }
    }

    this->is_redrawn.exchange(true);
}
