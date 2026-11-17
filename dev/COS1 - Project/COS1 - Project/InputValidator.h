#pragma once
#include <string>

class InputValidator
{
public:
    // --- VALIDATION UTILITIES ---

    // Checks if an entire string consists purely of numbers
    static bool IsValidNumber(const std::string& str);

    // Safely extracts and validates integer input within a specified range (plus debug flags)
    static int GetValidatedInt(int minRange, int maxRange);
};
//Organized and Refactored