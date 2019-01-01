#pragma once

#include <string>
#include "Symbols.hpp"
#include "Colours.hpp"

namespace Blame::Styles {
    struct Style {
        Blame::Styles::Symbols *symbols = new Symbols();
        Blame::Styles::Colours *colours = new Colours();
    };
}