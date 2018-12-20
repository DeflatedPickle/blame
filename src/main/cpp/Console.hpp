#pragma once

namespace Blame {
    class Console {
    public:
        Console();

        void mainloop();

        void clear();

        void moveCaret(int column, int row);

    protected:
        std::string colour_background;
    };
}