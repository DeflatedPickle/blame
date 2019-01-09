#include <functional>
#include <styles/StyleText.hpp>
#include "List.hpp"

Blame::Widgets::List::List(Blame::Console *console, Blame::Widgets::Widget *parent, std::vector<std::string> items, std::function<void()> command) : Widget(console, parent) {
    this->items = items;
    this->command = command;
    this->selection = 0;

    this->width = 8;
    this->height = (int) items.size() + 2;

    this->style = Blame::Styles::StyleText();
}

void Blame::Widgets::List::redraw() {
    Widget::redraw();

    this->widget_stream << this->getCurrentColour(this->style.colours.background_content);
    this->widget_stream << this->getCurrentColour(this->style.colours.text);

    int counter = 0;
    for (auto item : this->items) {
        this->console->moveCaret(this->widget_stream, this->column + 1, this->row + counter + 1);

        if (counter == this->selection) {
            this->widget_stream << Blame::Util::EscapeCodes::backgroundBlue();
        }

        this->widget_stream << item;
        this->widget_stream << Blame::Util::EscapeCodes::reset();

        counter++;
    }

    *this->console->buffer_list[!this->console->current_buffer] << this->widget_stream.str();
    this->widget_stream.str(std::string());

    this->is_redrawn.exchange(true);
}
