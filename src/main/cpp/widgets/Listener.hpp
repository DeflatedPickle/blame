#pragma once

#include "../util/ArrowKey.hpp"

namespace Blame::Widgets {
    class Listener {
    public:
        virtual void quit() = 0;

        virtual void arrowKey(Blame::Util::ArrowKey arrowKey) = 0;
    };
}