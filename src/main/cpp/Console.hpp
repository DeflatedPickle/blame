#pragma once

namespace Blame {
    class Console {
    public:
        Console();

        void clear();
        void moveCaret(int column, int row);
    };
}