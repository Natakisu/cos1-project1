#pragma once
#include <string>

class GameInput
{
public:
    static int GetValidatedInt(const std::string& prompt, int minVal, int maxVal);

    static int GetValidatedChoice(int minVal, int maxVal)
    {
        return GetValidatedInt("", minVal, maxVal);
    }

    static int GetValidatedChoice(const std::string& prompt, int minVal, int maxVal)
    {
        return GetValidatedInt(prompt, minVal, maxVal);
    }

    static void WaitForEnter(const std::string& prompt = "Press Enter to continue...");
};