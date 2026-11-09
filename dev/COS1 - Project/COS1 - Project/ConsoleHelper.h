#ifndef CONSOLE_HELPER_H
#include <string>

namespace ConsoleHelper
{
    // Struct to represent an ARGB or RGB color
    struct Color
    {
        int a, r, g, b;

        // Constructor defaulting alpha
        Color(int red, int green, int blue, int alpha)
            : r(red), g(green), b(blue), a(alpha) {
        }
    };

    // Predefined colors
    const Color Red(231, 76, 60, 255);
    const Color Orange(243, 156, 18, 255);
    const Color Yellow(241, 196, 15, 255);
    const Color Green(46, 204, 113, 255);
    const Color Blue(52, 152, 219, 255);
    const Color Indigo(75, 0, 130, 255);
    const Color Purple(139, 0, 255, 255);
    const Color Cyan(52, 152, 219, 255);
    const Color White(255, 255, 255, 255);
    const Color DarkGray(64, 64, 64, 255);

    // Custom print function
    void print(const std::string& text, const Color& color = White, bool newline = true);
}

#endif