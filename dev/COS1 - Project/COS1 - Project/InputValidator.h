#pragma once
#include <string>

class InputValidator
{
public:
    // Checks if an entire string consists purely of numbers
    static bool IsValidNumber(const std::string& str);

    static int GetValidatedInt(int minRange, int maxRange);
};