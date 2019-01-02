#pragma once

#include "../util/ArrowKey.hpp"
#include "../util/State.hpp"

namespace Blame::Widgets {
    class Listener {
    public:
        virtual void quit() = 0;

        virtual void focus() = 0;
        virtual void unfocus() = 0;

        virtual void arrowKey(Blame::Util::ArrowKey arrowKey) = 0;
        virtual void activate() = 0;

    protected:
        Blame::Util::State state = Blame::Util::State::NORMAL;
    };
}