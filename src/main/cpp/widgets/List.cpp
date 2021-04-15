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

    int iteration = 0;
    for (auto item = 0; item < this->items.size(); item++) {
        for (auto i = 0; i < this->items[item].length(); i++) {
            
            if (this->client_area.top + iteration < this->view_area.bottom - 2 &&
                this->client_area.left + i < this->view_area.right) {
                
                if ((item + this->view_area_offset_y) >= this->items.size()) {
                    std::cout << "[ ERR ]    This is the case where our current item index, ";
                    std::cout << " " << item << ", plus the view_area_offset_y, ";
                    std::cout << " " << view_area_offset_y << ", is far too high!! :o";
                    std::cout << std::endl;

                    std::cout << "[     ]    Notice that the only reason we\'re TRYING a redraw";
                    std::cout << " is because the y-axis iteration is " << iteration << std::endl;
                    std::cout << "[     ]    which is less than the \"bottom minus two\" i.e. " << (this->view_area.bottom - 2) << std::endl;
                    this->console->raw_grid[this->client_area.top + iteration][this->client_area.left + i] =
                            this->getCurrentColour(this->style.colours.background_content)
                            + (iteration == this->selection ? Blame::Util::EscapeCodes::backgroundBlue()
                                                            + Blame::Util::EscapeCodes::foregroundYellow()
                                                          : this->getCurrentColour(this->style.colours.text))
                            + this->items[item + this->view_area_offset_y][i + this->view_area_offset_x];
                } else {
                    this->console->raw_grid[this->client_area.top + iteration][this->client_area.left + i] =
                            this->getCurrentColour(this->style.colours.background_content)
                            + (iteration == this->selection ? Blame::Util::EscapeCodes::backgroundBlue()
                                                            + Blame::Util::EscapeCodes::foregroundYellow()
                                                          : this->getCurrentColour(this->style.colours.text))
                            + this->items[item + this->view_area_offset_y][i + this->view_area_offset_x];
                }
            }
        }

        iteration++;
    }

    this->is_redrawn.exchange(true);
}

