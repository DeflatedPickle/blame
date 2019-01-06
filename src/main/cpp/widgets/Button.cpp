#include <functional>
#include <styles/StyleButton.hpp>
#include "Button.hpp"

Blame::Widgets::Button::Button(Blame::Console *console, Blame::Widgets::Widget *parent, std::string text, std::function<void()> command) : Widget(console, parent) {
    this->text = text;
    this->command = command;

    this->width = 8;
    this->height = 3;

    this->style = Blame::Styles::StyleButton();
}

void Blame::Widgets::Button::redraw() {
    Widget::redraw();

    this->console->moveCaret(this->widget_stream, this->column + 1, this->row + 1);
    
    this->widget_stream << this->getCurrentColour(this->style.colours.background_content);
    this->widget_stream << this->getCurrentColour(this->style.colours.text);
    this->widget_stream << this->text;

    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

    this->is_redrawn.exchange(true);
}
