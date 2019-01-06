#pragma once

#include <util/EscapeCodes.hpp>
#include "Style.hpp"

namespace Blame::Styles {
    struct StyleText : Blame::Styles::Style {
        StyleText() {
            // Colours
            this->colours.border.normal = Blame::Util::EscapeCodes::foregroundBlack();
            this->colours.background_content.normal = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.background_border.normal = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.normal = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours.border.focused = Blame::Util::EscapeCodes::foregroundBlue();
            this->colours.background_content.focused = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.background_border.focused = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.focused = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours.border.disabled = Blame::Util::EscapeCodes::foregroundRed();
            this->colours.background_content.disabled = Blame::Util::EscapeCodes::backgroundBlack();
            this->colours.background_border.disabled = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.disabled = Blame::Util::EscapeCodes::foregroundWhite();

            // Symbols
            this->symbols.top_left = "┌";
            this->symbols.top_middle = "─";
            this->symbols.top_right = "┐";
            this->symbols.middle_left = "│";
            // this->symbols->middle_fill = "░";
            this->symbols.middle_fill = "█";
            this->symbols.middle_right = "│";
            this->symbols.bottom_left = "└";
            this->symbols.bottom_middle = "─";
            this->symbols.bottom_right = "┘";
        }
    };
}