#include "PreparationMenu.h"
#include "InventoryScreen.h"
#include "ConsoleHelper.h"
#include "GameInput.h"
#include <iostream>
#include <cstdlib>

void PreparationMenu::Open(Player* player)
{
    if (!player) return;

    bool preparing = true;

    while (preparing)
    {
        system("cls");
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("     [ PREPARATION & RELIC HUB ]  ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print(" Character: " + player->GetName() + " | Level: " + std::to_string(player->GetLevel()) + " | Shards: " + std::to_string(player->GetRelicShards()) + "rs", ConsoleHelper::White);
        ConsoleHelper::print(" HP: " + std::to_string(player->GetCurrentHP()) + "/" + std::to_string(player->GetMaxHP()), ConsoleHelper::White);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Review Full Character Stats", ConsoleHelper::White);
        ConsoleHelper::print("2. Open Inventory & Consumables", ConsoleHelper::White);
        ConsoleHelper::print("3. Inspect Equipped Weapons", ConsoleHelper::White);
        // Placeholder for future Item Shop:
        ConsoleHelper::print("4. Visit In-Game Item Shop [Coming Soon]", ConsoleHelper::White);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("5. Proceed to Boss Difficulty", ConsoleHelper::Green);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option (1-5): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(1, 5);

        if (choice == 1)
        {
            system("cls");
            ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
            ConsoleHelper::print("        [ CHARACTER STATS ]       ", ConsoleHelper::Cyan);
            ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
            player->DisplayStats();
            ConsoleHelper::print("\nPress Enter to return...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 2)
        {
            // Open the inventory management screen
            InventoryScreen::Open(player);
        }
        else if (choice == 3)
        {
            system("cls");
            ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
            ConsoleHelper::print("        [ EQUIPPED WEAPONS ]      ", ConsoleHelper::Cyan);
            ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
            player->InspectWeapons();
            ConsoleHelper::print("\nPress Enter to return...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 5)
        {
            preparing = false; // Exits the hub and moves forward to difficulty selection
        }
    }
}