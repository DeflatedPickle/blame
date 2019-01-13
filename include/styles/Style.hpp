#pragma once

#include <string>

#include <styles/Symbols.hpp>
#include <styles/Colours.hpp>

namespace Blame::Styles {
    struct Style {
        Blame::Styles::Symbols symbols = Symbols();
        Blame::Styles::Colours colours = Colours();
    };
}