#include <iostream>

#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>
#include <widgets/Button.hpp>
#include <widgets/Scale.hpp>
#include <util/Direction.hpp>
#include <util/State.hpp>

int main() {
    std::unique_ptr<Blame::Console> console(new Blame::Console());
    console->setTitle("Hello, World!");

    std::unique_ptr<Blame::Widgets::Window> window(new Blame::Widgets::Window(console.get(), "Hello World"));
    window->place(5, 5, 22, 18);

    std::unique_ptr<Blame::Widgets::Text> text(new Blame::Widgets::Text(console.get(), window.get()));
    text->pack(Blame::Util::Direction::DOWN);

    std::shared_ptr<Blame::Widgets::Button> button(new Blame::Widgets::Button(console.get(), window.get(), "Click Me", nullptr));
    button->command = [=]() { button->text = "Clicked!"; };
    button->pack(Blame::Util::Direction::DOWN);

    std::shared_ptr<Blame::Widgets::Scale> scale(new Blame::Widgets::Scale(console.get(), window.get(), Blame::Util::Orientation::HORIZONTAL, nullptr));
    scale->pack(Blame::Util::Direction::DOWN);
    scale->min = -1;
    scale->max = 1;

    std::shared_ptr<Blame::Widgets::Text> scale_text(new Blame::Widgets::Text(console.get(), window.get()));
    scale_text->pack(Blame::Util::Direction::DOWN);
    scale_text->width = 8;
    scale_text->height = 3;
    scale_text->state = Blame::Util::State::DISABLED;

    scale->command = [=]() { scale_text->content[0] = std::to_string(scale->current); };

    console->mainLoop();

    return 0;
}
