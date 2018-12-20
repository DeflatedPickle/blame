#include <cstdio>
#include <iostream>
#include "Console.hpp"
#include "util/EscapeCodes.hpp"

Blame::Console::Console() {
    this->clear();
    this->moveCaret(0, 0);

    this->colour_background = Blame::Util::EscapeCodes::foregroundYellow();

    std::cout << this->colour_background;
}

void Blame::Console::mainloop() {
    while (true) {

    }
}

void Blame::Console::moveCaret(int column, int row) {
    printf("\033[%d;%dH", row, column);
}

void Blame::Console::clear() {
    std::cout << Blame::Util::EscapeCodes::reset();
    printf("\033c");
}
