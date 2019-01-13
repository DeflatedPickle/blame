#pragma once

#include <styles/Style.hpp>

namespace Blame::Styles {
    struct StyleWindow : Blame::Styles::Style {
        StyleWindow() {
            // Colours
            this->colours.border.normal = Blame::Util::EscapeCodes::foregroundCyan();
            this->colours.background_content.normal = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.normal = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours.border.focused = Blame::Util::EscapeCodes::foregroundGreen();
            this->colours.background_content.focused = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.focused = Blame::Util::EscapeCodes::foregroundBlack();

            // Symbols
            this->symbols.top_left = "╔";
            this->symbols.top_middle = "═";
            this->symbols.top_right = "╗";
            this->symbols.middle_left = "║";
            // this->symbols.middle_fill = "░";
            this->symbols.middle_fill = "█";
            this->symbols.middle_right = "║";
            this->symbols.bottom_left = "╚";
            this->symbols.bottom_middle = "═";
            this->symbols.bottom_right = "╝";
        }
    };
}