#include "InventoryScreen.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <cstdlib>

void InventoryScreen::Open(Player* player)
{
    if (!player) return;

    bool managingInventory = true;

    while (managingInventory)
    {
        system("cls");
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("      [ PLAYER INVENTORY ]        ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);

        const auto& inv = player->GetInventory();

        if (inv.empty())
        {
            ConsoleHelper::print("\n[!] Your inventory is completely empty.", ConsoleHelper::Yellow);
        }
        else
        {
            for (size_t i = 0; i < inv.size(); ++i)
            {
                std::cout << i + 1 << ". ";
                inv[i]->DisplayItemInfo();
            }
        }

        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Use an Item", ConsoleHelper::White);
        ConsoleHelper::print("0. Back to Main Menu", ConsoleHelper::White);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option: ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(0, 1);

        if (choice == 0)
        {
            managingInventory = false;
        }
        else if (choice == 1 && !inv.empty())
        {
            ConsoleHelper::print("Enter item number to use (0 to cancel): ", ConsoleHelper::Cyan, false);
            int itemChoice = GameInput::GetValidatedChoice(0, (int)inv.size());

            if (itemChoice > 0)
            {
                // Note: UseItem takes the vector index (itemChoice - 1)
                player->UseItem(itemChoice - 1);

                ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::White, false);
                std::string dummy;
                std::getline(std::cin, dummy);
            }
        }
    }
}