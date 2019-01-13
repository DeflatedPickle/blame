#pragma once

#include <string>

#include <StateColours.hpp>

namespace Blame::Styles {
    struct Colours {
        Blame::Styles::StateColours border;
        Blame::Styles::StateColours background_border;
        Blame::Styles::StateColours background_content;
        Blame::Styles::StateColours text;
    };
}
