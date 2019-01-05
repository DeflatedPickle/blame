#pragma once

#include <util/Direction.hpp>
#include <util/State.hpp>

namespace Blame::Widgets {
    class Listener {
    public:
        virtual void quit() = 0;

        virtual void focus() = 0;
        virtual void focus(long pos) = 0;
        virtual void unfocus() = 0;

        virtual void move(Blame::Util::Direction direction) = 0;
        virtual void activate() = 0;
        virtual void text(std::string text) = 0;

        Blame::Util::State state = Blame::Util::State::NORMAL;
    };
}