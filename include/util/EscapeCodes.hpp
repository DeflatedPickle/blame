#pragma once

#include <string>

namespace Blame::Util {
    class EscapeCodes {
    public:
        static std::string cursorUp() {
            return "\u001b[{n}A";
        }

        static std::string cursorDown() {
            return "\u001b[{n}B";
        }

        static std::string cursorRight() {
            return "\u001b[{n}C";
        }

        static std::string cursorLeft() {
            return "\u001b[{n}D";
        }

        static std::string caretOff() {
            return "\u001b[?25l";
        }

        static std::string caretOn() {
            return "\u001b[?25h";
        }

        static std::string reset() {
            return "\u001b[0m";
        }

        static std::string bold() {
            return "\u001b[1m";
        }

        static std::string underline() {
            return "\u001b[4m";
        }

        static std::string reversed() {
            return "\u001b[7m";
        }

        static std::string foregroundBlack() {
            return "\u001b[30m";
        }

        static std::string backgroundBlack() {
            return "\u001b[40m";
        }

        static std::string brightBlack() {
            return "\u001b[30;1m";
        }

        static std::string backgroundBrightBlack() {
            return "\u001b[40;1m";
        }

        static std::string foregroundRed() {
            return "\u001b[31m";
        }

        static std::string backgroundRed() {
            return "\u001b[41m";
        }

        static std::string foregroundBrightRed() {
            return "\u001b[31;1m";
        }

        static std::string backgroundBrightRed() {
            return "\u001b[41;1m";
        }

        static std::string foregroundGreen() {
            return "\u001b[32m";
        }

        static std::string backgroundGreen() {
            return "\u001b[42m";
        }

        static std::string foregroundBrightGreen() {
            return "\u001b[32;1m";
        }

        static std::string backgroundBrightGreen() {
            return "\u001b[42;1m";
        }

        static std::string foregroundYellow() {
            return "\u001b[33m";
        }

        static std::string backgroundYellow() {
            return "\u001b[43m";
        }

        static std::string foregroundBrightYellow() {
            return "\u001b[33;1m";
        }

        static std::string backgroundBrightYellow() {
            return "\u001b[43;1m";
        }

        static std::string foregroundBlue() {
            return "\u001b[34m";
        }

        static std::string backgroundBlue() {
            return "\u001b[44m";
        }

        static std::string foregroundBrightBlue() {
            return "\u001b[34;1m";
        }

        static std::string backgroundBrightBlue() {
            return "\u001b[44;1m";
        }

        static std::string foregroundMagenta() {
            return "\u001b[35m";
        }

        static std::string backgroundMagenta() {
            return "\u001b[45m";
        }

        static std::string foregroundBrightMagenta() {
            return "\u001b[35;1m";
        }

        static std::string backgroundBrightMagenta() {
            return "\u001b[45;1m";
        }

        static std::string foregroundCyan() {
            return "\u001b[36m";
        }

        static std::string backgroundCyan() {
            return "\u001b[46m";
        }

        static std::string foregroundBrightCyan() {
            return "\u001b[36;1m";
        }

        static std::string backgroundBrightCyan() {
            return "\u001b[46;1m";
        }

        static std::string foregroundWhite() {
            return "\u001b[37m";
        }

        static std::string backgroundWhite() {
            return "\u001b[47m";
        }

        static std::string foregroundBrightWhite() {
            return "\u001b[37;1m";
        }

        static std::string backgroundBrightWhite() {
            return "\u001b[47;1m";
        }
    };
}