#include "GameInput.h"
#include "InputValidator.h"
#include "ConsoleHelper.h"
#include <iostream>

int GameInput::GetValidatedChoice(int minRange, int maxRange, int debugOption)
{
    int choice = 0;
    std::string inputLine;
    bool isValid = false;

    while (!isValid)
    {
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }

        ConsoleHelper::print("Choice: ", ConsoleHelper::Cyan, false);

        if (!std::getline(std::cin, inputLine) || inputLine.empty())
        {
            continue;
        }

        if (InputValidator::IsValidNumber(inputLine))
        {
            choice = std::stoi(inputLine);
            if ((choice >= minRange && choice <= maxRange) || choice == debugOption)
            {
                isValid = true;
            }
            else
            {
                ConsoleHelper::print("[!] Invalid choice. Please enter a valid number.", ConsoleHelper::Red);
            }
        }
        else
        {
            ConsoleHelper::print("[!] Invalid input. Please enter numbers only.", ConsoleHelper::Red);
        }
    }

    return choice;
}