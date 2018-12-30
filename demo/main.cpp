#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");

    auto window = new Blame::Widgets::Window(console, "Hello World");
    window->place(5, 5, 20, 10);

    auto window_two = new Blame::Widgets::Window(console, "Another Window");
    window_two->place(40, 8, 30, 10);

    console->mainLoop();

    return 0;
}