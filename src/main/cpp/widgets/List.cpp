#include <widgets/List.hpp>

#include <functional>

#include <styles/StyleText.hpp>

Blame::Widgets::List::List(Blame::Console *console, Blame::Widgets::Widget *parent, std::vector<std::string> items,
                           std::function<void()> command) : Widget(console, parent) {
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
            this->console->raw_grid[this->client_area.top + counter][this->client_area.left + i] =
                    this->getCurrentColour(this->style.colours.background_content)
                    + (counter == this->selection ? Blame::Util::EscapeCodes::backgroundBlue()
                                                    + Blame::Util::EscapeCodes::foregroundYellow()
                                                  : this->getCurrentColour(this->style.colours.text))
                    + item[i];
        }

        counter++;
    }

    this->is_redrawn.exchange(true);
}
