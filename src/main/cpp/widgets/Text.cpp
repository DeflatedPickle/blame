#include "Text.hpp"
#include "../styles/StyleButton.hpp"

Blame::Widgets::Text::Text(Blame::Console *console, Blame::Widgets::Widget *parent) : Widget(console, parent) {
    this->height = 6;
    this->width = 12;

    this->symbol_caret = "_";
    this->colour_caret = Blame::Util::EscapeCodes::foregroundBrightMagenta();

    this->style = new Blame::Styles::StyleButton();

    this->caret_x = 0;
    this->caret_y = 0;
}

void Blame::Widgets::Text::redraw() {
    Widget::redraw();

    this->console->moveCaret(this->widget_stream, this->client_area.left, this->client_area.top);
    this->widget_stream << this->style->colours->background;
    this->widget_stream << this->style->colours->text;

    this->widget_stream << this->content;

    this->console->moveCaret(this->widget_stream, this->client_area.left + this->caret_x, this->client_area.top + this->caret_y);
    this->widget_stream << this->colour_caret;
    this->widget_stream << this->symbol_caret;

    this->widget_stream << Blame::Util::EscapeCodes::reset();

    this->is_redrawn.exchange(true);
}

void Blame::Widgets::Text::move(Blame::Util::Direction direction) {
    if (this != this->console->focused_widget)
        return;

    switch (direction) {
        case Blame::Util::Direction::UP:
            this->caret_y--;
            break;

        case Blame::Util::Direction::DOWN:
            this->caret_y++;
            break;

        case Blame::Util::Direction::LEFT:
            this->caret_x--;
            break;

        case Blame::Util::Direction::RIGHT:
            this->caret_x++;
            break;
    }
}

void Blame::Widgets::Text::text(std::string text) {
    this->content.insert((unsigned long)this->caret_x, text);
    this->caret_x++;
}
