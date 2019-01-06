#include <iostream>
#include <Console.hpp>
#include <widgets/Window.hpp>
#include <widgets/Text.hpp>
#include <widgets/Button.hpp>
#include <widgets/Scale.hpp>
class Demos{
private:
    Blame::Console          *console;
    Blame::Widgets::Window  *window;
    Blame::Widgets::Text    *text,
                            *scale_text;
    Blame::Widgets::Button  *button;
    Blame::Widgets::Scale   *scale;
public:
    Demos(){
        console = new Blame::Console();
        console->setTitle("Hello, World!");

        window = new Blame::Widgets::Window(console, "Hello World");
        window->place(5, 5, 22, 18);

        text = new Blame::Widgets::Text(console, window);
        text->pack(Blame::Util::Direction::DOWN);

        button = new Blame::Widgets::Button(console, window, "Click Me", nullptr);
        button->command = [=]() {button->text = "Clicked!";};
        button->pack(Blame::Util::Direction::DOWN);

        scale = new Blame::Widgets::Scale(console, window, Blame::Util::Orientation::HORIZONTAL, nullptr);
        scale->pack(Blame::Util::Direction::DOWN);
        scale->min = -1;
        scale->max = 1;

        scale_text = new Blame::Widgets::Text(console, window);
        scale_text->pack(Blame::Util::Direction::DOWN);
        scale_text->width = 8;
        scale_text->height = 3;
        scale_text->state = Blame::Util::State::DISABLED;

        scale->command = [=](){
            scale_text->content.push_back(std::to_string(scale->current));
        };

        console->mainLoop();
    }
    ~Demos(){
        delete console;
        delete window;
        delete text;
        delete button;
        delete scale;
        delete scale_text;
    }
};
int main() {
    Demos demos;
    return 0;
}
