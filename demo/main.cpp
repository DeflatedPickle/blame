#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"
#include "../src/main/cpp/widgets/Button.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");

    auto window = new Blame::Widgets::Window(console, "Hello World");
    window->place(5, 5, 20, 10);

    auto button = new Blame::Widgets::Button(console, window, "Click Me", nullptr);
    button->command = [=]() {button->text = "Clicked!";};
    button->pack();

    auto window_two = new Blame::Widgets::Window(console, "Another Window");
    window_two->place(40, 8, 30, 10);

    console->mainLoop();

    return 0;
}