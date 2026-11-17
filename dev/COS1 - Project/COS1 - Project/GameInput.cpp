#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <stdexcept>

int GameInput::GetValidatedInt(const std::string& prompt, int minVal, int maxVal)
{
    while (true)
    {
        if (!prompt.empty())
        {
            std::cout << prompt;
        }

        std::string input;
        if (!std::getline(std::cin, input))
        {
            std::cin.clear();
            continue;
        }

        // Trim leading/trailing whitespace
        size_t start = input.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
        {
            ConsoleHelper::print("[!] Invalid input. Please enter a number between " +
                std::to_string(minVal) + " and " + std::to_string(maxVal) + ".", ConsoleHelper::Red);
            continue;
        }
        size_t end = input.find_last_not_of(" \t\r\n");
        input = input.substr(start, end - start + 1);

        try
        {
            size_t processedChars = 0;
            int value = std::stoi(input, &processedChars);

            // Reject partial parses like "2abc"
            if (processedChars != input.length())
            {
                throw std::invalid_argument("Trailing characters");
            }

            if (value < minVal || value > maxVal)
            {
                ConsoleHelper::print("[!] Choice out of range (" + std::to_string(minVal) +
                    "-" + std::to_string(maxVal) + "). Try again.", ConsoleHelper::Yellow);
                continue;
            }

            return value;
        }
        catch (const std::invalid_argument&)
        {
            ConsoleHelper::print("[!] Invalid input. Please enter a valid number.", ConsoleHelper::Red);
        }
        catch (const std::out_of_range&)
        {
            ConsoleHelper::print("[!] Number is too large. Please enter a number between " +
                std::to_string(minVal) + " and " + std::to_string(maxVal) + ".", ConsoleHelper::Red);
        }
    }
}

void GameInput::WaitForEnter(const std::string& prompt)
{
    ConsoleHelper::print(prompt, ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}