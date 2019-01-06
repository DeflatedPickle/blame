#pragma once

#include <string>
#include "Symbols.hpp"
#include "Colours.hpp"

namespace Blame::Styles {
    struct Style {
        Blame::Styles::Symbols symbols = Symbols();
        Blame::Styles::Colours colours = Colours();
    };
}