#ifndef CONSOLE_HELPER_H
#include <string>

namespace ConsoleHelper
{
    // Struct to represent an ARGB or RGB color
    struct Color
    {
        int a, r, g, b;

        // Constructor defaulting alpha
        Color(int red, int green, int blue, int alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {
        }
    };

    // Predefined colors
    const Color Red(231, 76, 60);
    const Color Green(46, 204, 113);
    const Color Cyan(52, 152, 219);
    const Color Yellow(241, 196, 15);
    const Color White(255, 255, 255);

    // Custom print function
    void print(const std::string& text, const Color& color = White, bool newline = true);
}

#endif