#pragma once

#include <string>

namespace Blame::Styles {
    struct Colours {
        std::string border;
        std::string background;
        std::string text;

        std::string focus_border;
        std::string focus_background;
        std::string focus_text;

        std::string disable_border;
        std::string disable_background;
        std::string disable_text;
    };
}