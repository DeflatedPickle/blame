#include <iostream>
#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>

int main() {
    auto console = new Blame::Console();
    console->setTitle("Dim");

    auto window = new Blame::Widgets::Window(console, "Dim");
    window->place(1, 1, 10, 10);
    window->fullscreen();
    window->state = Blame::Util::State::DISABLED;
    console->focus_order.pop_back();

    window->style->symbols->middle_fill = " ";

    auto text = new Blame::Widgets::Text(console, window);
    text->pack(Blame::Util::Direction::DOWN);
    text->width = console->width - 4;
    text->height = console->height - 3;
    text->focus();

    text->style->symbols->middle_fill = " ";

    auto new_colours = new Blame::Styles::Colours();
    new_colours->border = text->style->colours->border;
    new_colours->text.focused = Blame::Util::EscapeCodes::foregroundWhite();

    text->style->colours = new_colours;

    console->mainLoop();

    return 0;
}