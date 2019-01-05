#include <iostream>
#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>
#include <widgets/Button.hpp>
#include <widgets/Scale.hpp>

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");
    // console->setTitle(std::to_string(console->width) + "x" + std::to_string(console->height) + "=" + std::to_string(console->width * console->height));

    auto window = new Blame::Widgets::Window(console, "Hello World");
    window->place(5, 5, 22, 18);

    auto text = new Blame::Widgets::Text(console, window);
    text->pack(Blame::Util::Direction::DOWN);

    auto button = new Blame::Widgets::Button(console, window, "Click Me", nullptr);
    button->command = [=]() {button->text = "Clicked!";};
    button->pack(Blame::Util::Direction::DOWN);

    auto scale = new Blame::Widgets::Scale(console, window, Blame::Util::Orientation::HORIZONTAL, nullptr);
    scale->pack(Blame::Util::Direction::DOWN);
    scale->min = -1;
    scale->max = 1;

    auto scale_text = new Blame::Widgets::Text(console, window);
    scale_text->pack(Blame::Util::Direction::DOWN);
    scale_text->width = 8;
    scale_text->height = 3;
    scale_text->state = Blame::Util::State::DISABLED;

    scale->command = [=]() {scale_text->content = std::to_string(scale->current);};

    // auto window_two = new Blame::Widgets::Window(console, "Another Window");
    // window_two->place(40, 8, 30, 10);

    console->mainLoop();

    return 0;
}