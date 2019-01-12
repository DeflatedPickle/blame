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

    int counter = 0;
    for (const auto &item : this->items) {
        for (auto i = 0; i < item.length(); i++) {
            this->console->cell_info[this->row + 1 + counter][this->column + 1 + i] =
                    this->getCurrentColour(this->style.colours.background_content)
                    + this->getCurrentColour(this->style.colours.text)
                    + (counter == this->selection ? Blame::Util::EscapeCodes::backgroundBlue() : "")
                    + item[i];
        }

        counter++;
    }

    this->is_redrawn.exchange(true);
}
