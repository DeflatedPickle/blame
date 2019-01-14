#include <widgets/Scroll.hpp>

#include <cmath>
#include <functional>

#include <styles/StyleScaleHorizontal.hpp>
#include <styles/StyleScaleVertical.hpp>

Blame::Widgets::Scroll::Scroll(Blame::Console *console, Blame::Widgets::Widget *parent, Blame::Util::Orientation orientation, Blame::Widgets::Widget *widget) : Widget(console, parent) {
    this->orientation = orientation;
    this->widget = widget;

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

    this->colour_handle = Blame::Util::EscapeCodes::foregroundBlue();
}

void Blame::Widgets::Scroll::redraw() {
    Widget::redraw();

    switch (this->orientation) {
        case Blame::Util::Orientation::HORIZONTAL:
            for (auto i = 0; i < this->handle_size; i++) {
                if (this->client_area.left + this->current + i < this->console->width) {
                    this->console->raw_grid[this->client_area.top][this->client_area.left + this->current + i] =
                            this->getCurrentColour(this->style.colours.background_content)
                            + this->colour_handle
                            + this->symbol_handle;
                }
            }
            break;

        case Blame::Util::Orientation::VERTICAL:
            for (auto i = 0; i < this->handle_size; i++) {
                if (this->client_area.top + this->current + i < this->console->height) {
                    this->console->raw_grid[this->client_area.top + this->current + i][this->client_area.left] =
                            this->getCurrentColour(this->style.colours.background_content)
                            + this->colour_handle
                            + this->symbol_handle;
                }
            }
            break;
    }

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Scroll::move(Blame::Util::Direction direction) {
    if (this != this->console->focused_widget)
        return;

    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->handle_current - 1 > this->handle_min - 1 && this->orientation == Blame::Util::Orientation::VERTICAL) {
                this->handle_current--;
                this->widget->view_area_offset_y--;
            }
            break;

        case Blame::Util::Direction::DOWN:
            if (this->handle_current + 1 < this->handle_max - 2 && this->orientation == Blame::Util::Orientation::VERTICAL) {
                this->handle_current++;
                this->widget->view_area_offset_y++;
            }
            break;

        case Blame::Util::Direction::LEFT:
            if (this->handle_current - 1 > this->handle_min - 1 && this->orientation == Blame::Util::Orientation::HORIZONTAL) {
                this->handle_current--;
                this->widget->view_area_offset_x--;
            }
            break;

        case Blame::Util::Direction::RIGHT:
            if (this->handle_current + 1 < this->handle_max && this->orientation == Blame::Util::Orientation::HORIZONTAL) {
                this->handle_current++;
                this->widget->view_area_offset_x++;
            }
            break;
    }

    this->current = (this->handle_max / this->handle_size) * this->handle_current;

    Widget::move(direction);
}
