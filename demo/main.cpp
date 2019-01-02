#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"
#include "../src/main/cpp/widgets/Button.hpp"
#include "../src/main/cpp/widgets/Text.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");
    // console->setTitle(std::to_string(console->width) + "x" + std::to_string(console->height) + "=" + std::to_string(console->width * console->height));

    auto window = new Blame::Widgets::Window(console, "Hello World");
    window->place(5, 5, 22, 12);

    auto text = new Blame::Widgets::Text(console, window);
    text->pack(Blame::Util::Direction::DOWN);

    auto button = new Blame::Widgets::Button(console, window, "Click Me", nullptr);
    button->command = [=]() {button->text = "Clicked!";};
    button->pack(Blame::Util::Direction::DOWN);

    // auto window_two = new Blame::Widgets::Window(console, "Another Window");
    // window_two->place(40, 8, 30, 10);

    console->mainLoop();

    return 0;
}