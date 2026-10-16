#include "ConsoleHelper.h"
#include <iostream>

namespace ConsoleHelper
{
    void print(const std::string& text, const Color& color, bool newline)
    {
        std::cout << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b << "m"
            << text
            << "\033[0m"; 

        if (newline)
        {
            std::cout << "\n";
        }
    }
}