#pragma once
#include <string>

class GameInput
{
public:
    static int GetValidatedChoice(int minRange, int maxRange, int debugOption = -1);
};