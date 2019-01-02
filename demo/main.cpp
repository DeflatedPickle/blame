#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"
#include "../src/main/cpp/widgets/Button.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");
    // console->setTitle(std::to_string(console->width) + "x" + std::to_string(console->height) + "=" + std::to_string(console->width * console->height));

    auto window = new Blame::Widgets::Window(console, "Hello World");
    window->place(5, 5, 20, 10);

    auto button = new Blame::Widgets::Button(console, window, "Click Me", nullptr);
    button->command = [=]() {button->text = "Clicked!";};
    button->pack(Blame::Util::Direction::DOWN);

    auto button_two = new Blame::Widgets::Button(console, window, "Also Me", nullptr);
    button_two->command = [=]() {button_two->text = "Clicked!";};
    button_two->pack(Blame::Util::Direction::DOWN);

    auto window_two = new Blame::Widgets::Window(console, "Another Window");
    window_two->place(40, 8, 30, 10);

    console->mainLoop();

    return 0;
}