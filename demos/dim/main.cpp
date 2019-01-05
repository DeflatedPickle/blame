#include <iostream>
#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>

int main() {
    auto console = new Blame::Console();
    console->setTitle("Dim");

    auto window = new Blame::Widgets::Window(console, "Dim");
    window->place(1, 1, 10, 10);
    window->maximize();
    window->state = Blame::Util::State::DISABLED;

    auto text = new Blame::Widgets::Text(console, window);
    text->pack(Blame::Util::Direction::DOWN);
    text->width = console->width - 4;
    text->height = console->height - 3;
    text->focus();

    console->mainLoop();

    return 0;
}