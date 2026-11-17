#include "ConsoleHelper.h"
#include <iostream>

namespace ConsoleHelper
{
    // --- CONSOLE UTILITIES ---

    void print(const std::string& text, const Color& color, bool newline)
    {
        // Renders ANSI 24-bit TrueColor escape sequence, text, and resets format
        std::cout << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b << "m"
            << text
            << "\033[0m";

        if (newline)
        {
            std::cout << "\n";
        }
    }
}
//Organized and Refactored