#include "InputValidator.h"
#include <iostream>
#include <cctype>

// --- STRING VALIDATION UTILITIES ---
bool InputValidator::IsValidNumber(const std::string& str)
{
    if (str.empty()) return false;

    for (char c : str)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

// --- SAFE INPUT EXTRACTION ---
int InputValidator::GetValidatedInt(int minRange, int maxRange)
{
    std::string inputLine;
    int choice = -1;
    bool isValid = false;

    while (!isValid)
    {
        std::getline(std::cin, inputLine);

        if (IsValidNumber(inputLine))
        {
            choice = std::stoi(inputLine);

            // Allow range bounds as well as the special debug flag (9)
            if ((choice >= minRange && choice <= maxRange) || choice == 9)
            {
                isValid = true;
            }
            else
            {
                std::cout << "[!] Choice out of range. Please enter a valid option ("
                    << minRange << "-" << maxRange << "): ";
            }
        }
        else
        {
            std::cout << "[!] Invalid input. Please enter numbers only: ";
        }
    }

    return choice;
}
//Organized and Refactored