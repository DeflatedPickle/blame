#include "Text.hpp"
#include "../styles/StyleText.hpp"

// TODO: Add support for multiple text caret's
// TODO: Add support for selecting text
Blame::Widgets::Text::Text(Blame::Console *console, Blame::Widgets::Widget *parent) : Widget(console, parent) {
    this->height = 6;
    this->width = 12;

    this->symbol_caret = "_";
    this->colour_caret = Blame::Util::EscapeCodes::foregroundMagenta();

    this->style = new Blame::Styles::StyleText();

    this->caret_x = 0;
    this->caret_y = 0;
}

void Blame::Widgets::Text::redraw() {
    Widget::redraw();

    this->console->moveCaret(this->widget_stream, this->client_area.left, this->client_area.top);
    this->widget_stream << this->getCurrentColour(this->style->colours->background_content);
    this->widget_stream << this->getCurrentColour(this->style->colours->text);

    this->widget_stream << this->content;

    this->console->moveCaret(this->widget_stream, this->client_area.left + this->caret_x, this->client_area.top + this->caret_y);
    this->widget_stream << this->colour_caret;
    this->widget_stream << this->symbol_caret;

    this->widget_stream << Blame::Util::EscapeCodes::reset();
    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Text::move(Blame::Util::Direction direction) {
    if (this != this->console->focused_widget)
        return;

    switch (direction) {
        case Blame::Util::Direction::UP:
            if (this->caret_y - 1 > -1) {
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
    this->content.insert((unsigned long)this->caret_x, text);
    this->caret_x++;

    Widget::text(text);
}
