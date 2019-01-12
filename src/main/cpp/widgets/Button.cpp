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

    for (auto i = 0; i < this->text.length(); i++) {
        this->console->raw_grid[this->client_area.top][this->client_area.left + i] =
                this->getCurrentColour(this->style.colours.border)
                + this->getCurrentColour(this->style.colours.background_border)
                + this->text[i];
    }

    this->is_redrawn.exchange(true);
}
