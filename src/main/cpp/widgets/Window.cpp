#include "Window.hpp"

#include <iostream>
#include <styles/StyleWindow.hpp>

Blame::Widgets::Window::Window(Blame::Console *console, std::string title_text) : Widget(console, nullptr) {
    this->title_text = title_text;

    this->symbol_title_intersect_left = "╠";
    this->symbol_title_intersect_right = "╣";

    this->style = Blame::Styles::StyleWindow();
}

// FIXME: Draws the line under the title twice
void Blame::Widgets::Window::redraw() {
    if (this->state_window == Blame::Util::StateWindow::RESTORED || this->state_window == Blame::Util::StateWindow::MAXIMIZED) {
        this->is_redrawn.exchange(false);

        // Account for the title height
        this->row -= 2;

        for (int y = 0; y < 3; y++) {
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

                // Top Middle
                if (y == 0) {
                    this->console->raw_grid[this->row + y + 1][this->column + x] =
                            this->getCurrentColour(this->style.colours.border)
                            + this->getCurrentColour(this->style.colours.background_border)
                            + this->style.symbols.top_middle;
                }
                // Middle Fill
                else {
                    if (x >= 1 && x <= this->title_text.length()) {
                        this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                                this->getCurrentColour(this->style.colours.border)
                                + this->getCurrentColour(this->style.colours.background_content)
                                + this->title_text[x - 1];
                    }
                    // Text
                    else if (x == 0 || x > this->title_text.length()) {
                        this->console->raw_grid[this->row + y + 1][this->column + x + 1] =
                                this->getCurrentColour(this->style.colours.background_content)
                                + this->style.symbols.middle_fill;
                    }
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
            }
        }

        this->style.symbols.top_left = this->symbol_title_intersect_left;
        this->style.symbols.top_right = this->symbol_title_intersect_right;

        this->row += 2;
    }

    Widget::redraw();

    this->style.symbols.top_left = "╔";
    this->style.symbols.top_right = "╗";

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Window::move(Blame::Util::Direction direction) {
    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->row - 2 > console->client_area.top) {
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
