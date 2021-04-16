#include <widgets/List.hpp>

#include <functional>

#include <styles/StyleText.hpp>

Blame::Widgets::List::List(Blame::Console *console, Blame::Widgets::Widget *parent, std::vector<std::string> content,
                           std::function<void()> command) : Scrollable(console, parent) {
    this->content = content;
    this->command = command;
    this->selection = 0;

    this->width = 8;
    this->height = (int) content.size() + 2;

    this->style = Blame::Styles::StyleText();
}

void Blame::Widgets::List::redraw() {
    Widget::redraw();

    int iteration = 0;
    for (auto item = 0; item < this->content.size(); item++) {
        for (auto i = 0; i < this->content[item].length(); i++) {
            if (this->client_area.top + iteration < this->view_area.bottom - 2
                && this->client_area.left + i < this->view_area.right) {
                this->console->raw_grid[this->client_area.top + iteration][this->client_area.left + i] =
                        this->getCurrentColour(this->style.colours.background_content)
                        + (iteration == this->selection ? Blame::Util::EscapeCodes::backgroundBlue()
                                                        + Blame::Util::EscapeCodes::foregroundYellow()
                                                      : this->getCurrentColour(this->style.colours.text))
                        + this->content[item + this->view_area_offset_y][i + this->view_area_offset_x];
            }
        }

        iteration++;
    }

    this->is_redrawn.exchange(true);
}
