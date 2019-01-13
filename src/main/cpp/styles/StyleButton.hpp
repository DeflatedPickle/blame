#pragma once

#include <util/EscapeCodes.hpp>
#include "Style.hpp"

namespace Blame::Styles {
    struct StyleButton : Blame::Styles::Style {
        StyleButton() {
            // Colours
            this->colours.border.normal = Blame::Util::EscapeCodes::foregroundBlack();
            this->colours.background_content.normal = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.background_border.normal = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.normal = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours.border.focused = Blame::Util::EscapeCodes::foregroundBlue();
            this->colours.background_content.focused = Blame::Util::EscapeCodes::backgroundCyan();
            this->colours.background_border.focused = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.focused = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours.border.active = Blame::Util::EscapeCodes::foregroundGreen();
            this->colours.background_content.active = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.background_border.active = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours.text.active = Blame::Util::EscapeCodes::foregroundBlack();

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