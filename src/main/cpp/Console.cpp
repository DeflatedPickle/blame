#include <cstdio>
#include <iostream>
#include "Console.hpp"

Blame::Console::Console() {
    this->clear();
    this->moveCaret(0, 0);
}

void Blame::Console::moveCaret(int column, int row) {
    printf("\033[%d;%dH", row, column);
}

void Blame::Console::clear() {
    printf("\033c");
}
