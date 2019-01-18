#include <iostream>
#include <experimental/filesystem>
#include <fstream>

#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>
#include <widgets/List.hpp>
#include <widgets/Scroll.hpp>

// TODO: Horizontal scrolling
// TODO: Scrolling file list
// TODO: Scrolling line numbers (multiple widgets)
// TODO: Change the list to a tree with expanding folders
// TODO: Syntax highlighting
int main() {
    std::shared_ptr<Blame::Console> console(new Blame::Console());
    console->setTitle("Dim");

    auto new_colours = Blame::Styles::Colours();
    new_colours.border.normal = Blame::Util::EscapeCodes::foregroundWhite();
    new_colours.border.focused = Blame::Util::EscapeCodes::foregroundBlue();
    new_colours.text.focused = Blame::Util::EscapeCodes::foregroundWhite();

    std::unique_ptr<Blame::Widgets::Window> window(new Blame::Widgets::Window(console.get(), "Dim"));
    window->style.symbols.middle_fill = " ";
    window->place(0, 0, 10, 10);
    window->fullscreen();
    window->state = Blame::Util::State::DISABLED;
    console->focus_order.pop_back();

    // Load files

    std::vector<std::string> file_paths;
    std::vector<std::string> file_names;

    for (const auto &file : std::experimental::filesystem::directory_iterator(std::experimental::filesystem::current_path())) {
        file_paths.push_back(file.path().string());
        file_names.push_back(file.path().string().substr(file.path().string().find_last_of("/\\") + 1));
    }

    // List

    std::shared_ptr<Blame::Widgets::List> list(new Blame::Widgets::List(console.get(), window.get(), file_names, nullptr));
    list->style.symbols.middle_fill = " ";
    list->style.colours = new_colours;
    list->place(1, 1, 18, console->height - 6);
    list->view_area_width = list->width;
    list->view_area_height = list->height;
    list->updateClientArea();
    list->updateViewArea();

    std::vector<Blame::Widgets::Widget *> list_vector;
    list_vector.emplace_back(list.get());

    std::shared_ptr<Blame::Widgets::Scroll> list_scroll_x(new Blame::Widgets::Scroll(console.get(), window.get(), Blame::Util::Orientation::HORIZONTAL, list_vector));
    list_scroll_x->style.colours = new_colours;
    list_scroll_x->place(list->column - 1, list->row + list->height, list->width, 3);
    list_scroll_x->handle_max = list_scroll_x->width;

    std::shared_ptr<Blame::Widgets::Scroll> list_scroll_y(new Blame::Widgets::Scroll(console.get(), window.get(), Blame::Util::Orientation::VERTICAL, list_vector));
    list_scroll_y->style.colours = new_colours;
    list_scroll_y->place(list->column + list->width + 1, 1, 1, console->height - 6);
    list_scroll_y->handle_max = list_scroll_y->height;

    // Line Numbers

    std::shared_ptr<Blame::Widgets::Text> line_numbers(new Blame::Widgets::Text(console.get(), window.get()));
    line_numbers->style.symbols.middle_fill = " ";
    line_numbers->style.colours = new_colours;
    line_numbers->place(list_scroll_y->column + list_scroll_y->width + 1, 1, 3, console->height - 6);
    line_numbers->state = Blame::Util::State::DISABLED;
    line_numbers->view_area_width = line_numbers->width;
    line_numbers->view_area_height = line_numbers->height;
    line_numbers->updateClientArea();
    line_numbers->updateViewArea();

    // Text

    std::shared_ptr<Blame::Widgets::Text> text(new Blame::Widgets::Text(console.get(), window.get()));
    text->style.symbols.middle_fill = " ";
    text->style.colours = new_colours;
    text->place(line_numbers->column + line_numbers->width + 1, 1, console->width - 4 - 12 - list->width - 2, console->height - 6);
    text->view_area_width = text->width;
    text->view_area_height = text->height;
    text->focus();
    text->updateClientArea();
    text->updateViewArea();

    std::vector<Blame::Widgets::Widget *> content_vector {line_numbers.get(), text.get()};

    std::shared_ptr<Blame::Widgets::Scroll> text_scroll_x(new Blame::Widgets::Scroll(console.get(), window.get(), Blame::Util::Orientation::HORIZONTAL, content_vector));
    text_scroll_x->style.colours = new_colours;
    text_scroll_x->place(text->column - 1, text->row + text->height, text->width, 3);
    text_scroll_x->handle_max = text_scroll_x->width;

    std::shared_ptr<Blame::Widgets::Scroll> text_scroll_y(new Blame::Widgets::Scroll(console.get(), window.get(), Blame::Util::Orientation::VERTICAL, content_vector));
    text_scroll_y->style.colours = new_colours;
    text_scroll_y->place(text->column + text->width + 1, 1, 1, console->height - 6);
    text_scroll_y->handle_max = text_scroll_y->height;

    // Open file in text widget

    list->command = [=]() {
        std::ifstream file(file_paths[list->selection]);
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));

        std::vector<std::string> new_content;

        int place = 0;
        for (auto c : content) {
            if (c == '\n') {
                place++;
            }
            else {
                if (new_content.size() <= place) {
                    new_content.emplace_back("");
                }

                new_content[place] = new_content[place] + c;
            }
        }

        std::vector<std::string> numbers;
        for (auto i = 1; i < new_content.size(); i++) {
            if (i < 10) {
                numbers.emplace_back("  " + std::to_string(i));
            }
            else if (i >= 10 && i < 100) {
                numbers.emplace_back(" " + std::to_string(i));
            }
            else {
                numbers.emplace_back(std::to_string(i));
            }
        }
        line_numbers->content = numbers;

        text->content = new_content;

        text_scroll_y->max = (int) new_content.size();
        text_scroll_y->handle_size = std::abs(text->view_area_height - 2 - (int) new_content.size()) % text_scroll_y->max;
    };

    console->mainLoop();

    return 0;
}