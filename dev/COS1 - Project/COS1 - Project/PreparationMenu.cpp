#include "PreparationMenu.h"
#include "InventoryScreen.h"
#include "ItemShop.h"
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
        ConsoleHelper::print("4. Visit In-Game Item Shop", ConsoleHelper::White);
        ConsoleHelper::print("5. [DEBUG] Developer Cheat Menu", ConsoleHelper::Yellow);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("6. Proceed to Boss Difficulty", ConsoleHelper::Green);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option (1-6): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(1, 6);

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
        else if (choice == 4)
        {
            // Open the Item Shop!
            ItemShop::Open(player);
        }
        else if (choice == 5)
        {
            OpenDebugMenu(player);
        }
        else if (choice == 6)
        {
            preparing = false; // Exits the hub and moves forward to difficulty selection
        }
    }
}
// DEBUG / Cheat Menu
void PreparationMenu::OpenDebugMenu(Player* player)
{
    bool inDebugMenu = true;
    while (inDebugMenu)
    {
        system("cls");
        ConsoleHelper::print("==================================", ConsoleHelper::Yellow);
        ConsoleHelper::print("        [ DEVELOPER CHEAT MENU ]   ", ConsoleHelper::Yellow);
        ConsoleHelper::print("==================================", ConsoleHelper::Yellow);
        ConsoleHelper::print("1. Add +10,000 Relic Shards", ConsoleHelper::White);
        ConsoleHelper::print("2. Add +1,000 XP (Level Up)", ConsoleHelper::White);
        ConsoleHelper::print("0. Return to Preparation Hub", ConsoleHelper::White);
        ConsoleHelper::print("==================================", ConsoleHelper::Yellow);
        ConsoleHelper::print("Select cheat option: ", ConsoleHelper::Yellow, false);

        int choice = GameInput::GetValidatedChoice(0, 2);

        if (choice == 1)
        {
            player->AddRelicShards(10000);
            ConsoleHelper::print("\n[+] Added 10,000 Relic Shards!", ConsoleHelper::Green);
            ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 2)
        {
            player->GainXP(1000);
            ConsoleHelper::print("\n[+] Added 1,000 XP!", ConsoleHelper::Green);
            ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 0)
        {
            inDebugMenu = false;
        }
    }
}