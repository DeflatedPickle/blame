#include <widgets/Text.hpp>

#include <styles/StyleText.hpp>

// TODO: Add support for multiple text caret's
// TODO: Add support for selecting text
Blame::Widgets::Text::Text(Blame::Console *console, Blame::Widgets::Widget *parent) : Widget(console, parent) {
    this->height = 6;
    this->width = 12;

    this->view_area_width = this->width;
    this->view_area_height = this->height;
    this->updateViewArea();

    this->symbol_caret = "_";
    this->colour_caret = Blame::Util::EscapeCodes::foregroundMagenta();

    this->style = Blame::Styles::StyleText();

    this->caret_x = 0;
    this->caret_y = 0;

    this->content.emplace_back("");
}

void Blame::Widgets::Text::redraw() {
    Widget::redraw();

    int iteration = 0;
    for (auto line = 0; line < this->content.size(); line++) {
        for (auto i = 0; i < this->content[line].length(); i++) {
            if (this->client_area.top + iteration < this->view_area.bottom
                && this->client_area.left + i < this->view_area.right) {
                this->console->raw_grid[this->client_area.top + iteration][this->client_area.left + i] =
                        this->getCurrentColour(this->style.colours.background_content)
                        + this->getCurrentColour(this->style.colours.text)
                        + this->content[line + this->view_area_offset_y][i + this->view_area_offset_x];
            }
        }
        iteration++;
    }

    if (this->state != Blame::Util::State::DISABLED) {
        this->console->raw_grid[this->client_area.top + this->caret_y][this->client_area.left + this->caret_x] =
                this->colour_caret
                + this->symbol_caret;
    }

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Text::move(Blame::Util::Direction direction) {
    if (this != this->console->focused_widget || this->state == Blame::Util::State::DISABLED)
        return;

    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->caret_y - 1 > -1) {
                this->caret_x = 0;
                this->caret_y--;
            }
            break;

        case Blame::Util::Direction::DOWN:
            if (this->caret_y + 1 < this->height - 2 && this->caret_y + 1 < this->content.size()) {
                this->caret_y++;

                if (this->content[this->caret_y].size() <= 1) {
                    this->caret_x = 0;
                }
            }
            break;

        case Blame::Util::Direction::LEFT:
            if (this->caret_x - 1 > -1) {
                this->caret_x--;
            }
            else {
                this->caret_y--;
                this->caret_x = (int) this->content[this->caret_y].size();
            }
            break;

        case Blame::Util::Direction::RIGHT:
            if (this->caret_x + 1 < this->width) {
                this->caret_x++;

                if (this->caret_x + 1 > this->content[this->caret_y].size() + 1) {
                    this->caret_x = 0;
                    this->move(Blame::Util::Direction::DOWN);
                }
            }
            break;
    }

    Widget::move(direction);
}

void Blame::Widgets::Text::text(std::string text) {
    if (this->state == Blame::Util::State::DISABLED)
        return;

    switch (text.c_str()[0]) {
        // Enter
        case '\n':
            this->caret_x = 0;
            this->caret_y++;

            if (this->caret_y >= this->content.size()) {
                this->content.emplace_back("");
            }
            break;

        // Space
        case ' ':
            this->content[this->caret_y].insert((unsigned long)this->caret_x, " ");
            this->caret_x++;
            break;

        // Backspace
        case 127:
            // FIXME: Doesn't work with multiline text
            if (this->caret_x - 1 > -1) {
                this->caret_x--;
            }

            this->content[this->caret_y].erase((unsigned long)this->caret_x, 1);
            break;

        // Everything else
        default:
            // this->console->setTitle(std::to_string(text.c_str()[0]));
            this->content[this->caret_y].insert((unsigned long)this->caret_x, text);
            this->caret_x++;
            break;
    }

    Widget::text(text);
}
