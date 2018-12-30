#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");

    auto window = new Blame::Widgets::Window(console, "Hello World", 5, 5, 20, 10);
    window->redraw();

    auto window_two = new Blame::Widgets::Window(console, "Another Window", 40, 8, 30, 10);
    window_two->redraw();

    console->mainloop();

    return 0;
}