#pragma once

#include "Style.hpp"
#include "../util/EscapeCodes.hpp"

namespace Blame::Styles {
    struct StyleWindow : Blame::Styles::Style {
        StyleWindow() {
            // Colours
            this->colours->border = Blame::Util::EscapeCodes::foregroundCyan();
            this->colours->background = Blame::Util::EscapeCodes::backgroundWhite();
            this->colours->text = Blame::Util::EscapeCodes::foregroundBlack();

            this->colours->focus_border = Blame::Util::EscapeCodes::foregroundGreen();

            // Symbols
            this->symbols->top_left = "╔";
            this->symbols->top_middle = "═";
            this->symbols->top_right = "╗";
            this->symbols->middle_left = "║";
            // this->symbols->middle_fill = "░";
            this->symbols->middle_fill = "█";
            this->symbols->middle_right = "║";
            this->symbols->bottom_left = "╚";
            this->symbols->bottom_middle = "═";
            this->symbols->bottom_right = "╝";
        }
    };
}