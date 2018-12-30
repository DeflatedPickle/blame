#include <iostream>
#include "../src/main/cpp/Console.hpp"
#include "../src/main/cpp/widgets/Window.hpp"

int main() {
    auto console = new Blame::Console();
    console->setTitle("Hello, World!");

    auto window = new Blame::Widgets::Window(console, "Hello World", 5, 5, 20, 10);
    window->redraw();

    console->mainloop();

    return 0;
}