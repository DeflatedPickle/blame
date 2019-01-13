#include <widgets/Scale.hpp>

#include <cmath>
#include <functional>

#include <styles/StyleScaleHorizontal.hpp>
#include <styles/StyleScaleVertical.hpp>

Blame::Widgets::Scale::Scale(Blame::Console *console, Blame::Widgets::Widget *parent, Blame::Util::Orientation orientation, std::function<void()> command) : Widget(console, parent) {
    this->orientation = orientation;
    this->command = command;

    // TODO: Smoothly transition through the handle parts to represent each segment of a float value
    switch (this->orientation) {
        case Blame::Util::Orientation::HORIZONTAL:
            this->width = 8;
            this->height = 3;

            this->symbol_handle = "█";

            this->style = Blame::Styles::StyleScaleHorizontal();
            break;

        case Blame::Util::Orientation::VERTICAL:
            this->width = 1;
            this->height = 8;

            this->symbol_handle = "█";

            this->style = Blame::Styles::StyleScaleVertical();
            break;
    }

    this->handle_current = 0;

    this->handle_min = 0;
    this->handle_max = 8;

    this->colour_handle = Blame::Util::EscapeCodes::foregroundMagenta();
}

void Blame::Widgets::Scale::redraw() {
    Widget::redraw();

    switch (this->orientation) {
        case Blame::Util::Orientation::HORIZONTAL:
            this->console->raw_grid[this->client_area.top][this->client_area.left + this->handle_current] =
                    this->getCurrentColour(this->style.colours.background_content)
                    + this->colour_handle
                    + this->symbol_handle;
            break;

        case Blame::Util::Orientation::VERTICAL:
            this->console->raw_grid[this->client_area.top + this->handle_current][this->client_area.left] =
                    this->getCurrentColour(this->style.colours.background_content)
                    + this->colour_handle
                    + this->symbol_handle;
            break;
    }

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Scale::move(Blame::Util::Direction direction) {
    if (this != this->console->focused_widget)
        return;

    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->handle_current - 1 > this->handle_min - 1 && this->orientation == Blame::Util::Orientation::VERTICAL) {
                this->handle_current--;
            }
            break;

        case Blame::Util::Direction::DOWN:
            if (this->handle_current + 1 < this->handle_max - 2 && this->orientation == Blame::Util::Orientation::VERTICAL) {
                this->handle_current++;
            }
            break;

        case Blame::Util::Direction::LEFT:
            if (this->handle_current - 1 > this->handle_min - 1 && this->orientation == Blame::Util::Orientation::HORIZONTAL) {
                this->handle_current--;
            }
            break;

        case Blame::Util::Direction::RIGHT:
            if (this->handle_current + 1 < this->handle_max && this->orientation == Blame::Util::Orientation::HORIZONTAL) {
                this->handle_current++;
            }
            break;
    }

    this->current = ((((float) this->handle_current / (this->handle_max - 1)) * this->max) - (std::fabs(this->min) / 2)) * (this->max - this->min);
    this->command();

    Widget::move(direction);
}
