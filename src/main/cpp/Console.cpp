#include <cstdio>
#include <iostream>
#include "Console.hpp"
#include "util/EscapeCodes.hpp"

Blame::Console::Console() {
    this->clear();
    this->moveCaret(0, 0);

    std::cout << Blame::Util::EscapeCodes::reset();
}
}

void Blame::Console::moveCaret(int column, int row) {
    printf("\033[%d;%dH", row, column);
}

void Blame::Console::clear() {
    printf("\033c");
}
