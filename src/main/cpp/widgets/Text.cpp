#include <styles/StyleText.hpp>
#include "Text.hpp"

// TODO: Add support for multiple text caret's
// TODO: Add support for selecting text
Blame::Widgets::Text::Text(Blame::Console *console, Blame::Widgets::Widget *parent) : Widget(console, parent) {
    this->height = 6;
    this->width = 12;

    this->symbol_caret = "_";
    this->colour_caret = Blame::Util::EscapeCodes::foregroundMagenta();

    this->style = Blame::Styles::StyleText();

    this->caret_x = 0;
    this->caret_y = 0;

    this->content.emplace_back("");
}

void Blame::Widgets::Text::redraw() {
    Widget::redraw();

    this->console->moveCaret(this->widget_stream, this->client_area.left, this->client_area.top);
    this->widget_stream << this->getCurrentColour(this->style.colours.background_content);
    this->widget_stream << this->getCurrentColour(this->style.colours.text);

    int iteration = 0;
    for (const auto &i : this->content) {
        this->console->moveCaret(this->widget_stream, this->client_area.left, this->client_area.top + iteration);
        this->widget_stream << i;
        iteration++;
    }

    if (this->state != Blame::Util::State::DISABLED) {
        this->console->moveCaret(this->widget_stream, this->client_area.left + this->caret_x, this->client_area.top + this->caret_y);
        this->widget_stream << this->colour_caret;
        this->widget_stream << this->symbol_caret;
    }

    this->widget_stream << Blame::Util::EscapeCodes::reset();
    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

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
            if (this->caret_y + 1 < this->height - 2) {
                this->caret_y++;
            }
            break;

        case Blame::Util::Direction::LEFT:
            if (this->caret_x - 1 > -1) {
                this->caret_x--;
            }
            break;

        case Blame::Util::Direction::RIGHT:
            if (this->caret_x + 1 < this->width) {
                this->caret_x++;
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
