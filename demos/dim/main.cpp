#include <iostream>
#include <experimental/filesystem>
#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>
#include <widgets/List.hpp>
#include <fstream>

int main() {
    std::shared_ptr<Blame::Console> console(new Blame::Console());
    console->setTitle("Dim");

    std::unique_ptr<Blame::Widgets::Window> window(new Blame::Widgets::Window(console.get(), "Dim"));
    window->place(1, 1, 10, 10);
    window->fullscreen();
    window->state = Blame::Util::State::DISABLED;
    console->focus_order.pop_back();

    window->style.symbols.middle_fill = " ";

    std::vector<std::string> file_paths;
    std::vector<std::string> file_names;

    for (const auto &file : std::experimental::filesystem::directory_iterator(std::experimental::filesystem::current_path())) {
        file_paths.push_back(file.path().string());
        file_names.push_back(file.path().string().substr(file.path().string().find_last_of("/\\") + 1));
    }

    std::shared_ptr<Blame::Widgets::List> list(new Blame::Widgets::List(console.get(), window.get(), file_names, nullptr));
    list->pack(Blame::Util::Direction::RIGHT);
    list->width = 18;
    list->height = console->height - 3;

    std::shared_ptr<Blame::Widgets::Text> text(new Blame::Widgets::Text(console.get(), window.get()));
    text->pack(Blame::Util::Direction::RIGHT);
    text->column += 10;
    text->width = console->width - 4 - list->width - 2;
    text->height = console->height - 3;
    text->focus();

    text->style.symbols.middle_fill = " ";

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

        text->content = new_content;
    };

    auto new_colours = Blame::Styles::Colours();
    new_colours.border = text->style.colours.border;
    new_colours.text.focused = Blame::Util::EscapeCodes::foregroundWhite();

    list->style.colours = new_colours;
    text->style.colours = new_colours;

    console->mainLoop();

    return 0;
}