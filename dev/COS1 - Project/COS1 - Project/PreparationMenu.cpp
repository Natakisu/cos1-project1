#include "PreparationMenu.h"
#include "InventoryScreen.h"
#include "ItemShop.h"
#include "CharacterManager.h"
#include "ConsoleHelper.h"
#include "GameInput.h"
#include <iostream>
#include <cstdlib>
#include "WeaponManager.h"

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

        if (player->GetUnspentPoints() > 0)
        {
            ConsoleHelper::print(" [!] Unspent Attribute Points: " + std::to_string(player->GetUnspentPoints()), ConsoleHelper::Green);
        }

        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Allocate / View Attributes", ConsoleHelper::White);
        ConsoleHelper::print("2. Assign / View Equipped Weapons", ConsoleHelper::White);
        ConsoleHelper::print("3. Open Inventory & Consumables", ConsoleHelper::White);
        ConsoleHelper::print("4. Visit In-Game Item Shop", ConsoleHelper::White);
        ConsoleHelper::print("5. [DEBUG] Developer Cheat Menu", ConsoleHelper::Yellow);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("6. Proceed to Boss Difficulty", ConsoleHelper::Green);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option (1-6): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(1, 6);

        if (choice == 1) // 1. Allocate / View Attributes
        {
            bool managingStats = true;
            while (managingStats)
            {
                system("cls");
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("     [ ATTRIBUTE MANAGEMENT ]     ", ConsoleHelper::Cyan);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);

                // If they have unspent points (like fresh characters with 30 points), run allocation first!
                if (player->GetUnspentPoints() > 0)
                {
                    ConsoleHelper::print("[+] You have " + std::to_string(player->GetUnspentPoints()) + " unspent attribute points available!", ConsoleHelper::Green);
                    ConsoleHelper::print("Press Enter to begin attribute allocation...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);

                    CharacterManager::RunAttributeAllocationMenu(player);

                    // Save progress after allocating
                    std::string saveFileName = player->GetName() + "_save.txt";
                    player->SaveToFile(saveFileName);

                    system("cls");
                }

                // View Current Stats
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("        [ CURRENT ATTRIBUTES ]    ", ConsoleHelper::Cyan);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                player->DisplayStats();

                ConsoleHelper::print("\n----------------------------------", ConsoleHelper::Cyan);
                ConsoleHelper::print("1. Allocate Points", ConsoleHelper::White);
                ConsoleHelper::print("0. Return to Prep Hub", ConsoleHelper::White);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("Select an option (0-1): ", ConsoleHelper::Cyan, false);

                int statChoice = GameInput::GetValidatedChoice(0, 1);
                if (statChoice == 1)
                {
                    if (player->GetUnspentPoints() > 0)
                    {
                        CharacterManager::RunAttributeAllocationMenu(player);

                        std::string saveFileName = player->GetName() + "_save.txt";
                        player->SaveToFile(saveFileName);
                    }
                    else
                    {
                        ConsoleHelper::print("\n[!] You have 0 unspent attribute points remaining!", ConsoleHelper::Yellow);
                        ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
                        std::string dummy;
                        std::getline(std::cin, dummy);
                    }
                }
                else
                {
                    managingStats = false;
                }
            }
        }

        else if (choice == 2) // 2. Assign / View Equipped Weapons
        {
            bool managingWeapons = true;
            while (managingWeapons)
            {
                system("cls");
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("       [ WEAPON LOADOUT HUB ]     ", ConsoleHelper::Cyan);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);

                // View current equipped weapons and skill tooltips
                player->InspectWeapons();

                ConsoleHelper::print("\n----------------------------------", ConsoleHelper::Cyan);
                ConsoleHelper::print("1. Assign / Select New Weapons", ConsoleHelper::White);
                ConsoleHelper::print("2. Swap Active Weapon (Primary <-> Secondary)", ConsoleHelper::White);
                ConsoleHelper::print("0. Return to Prep Hub", ConsoleHelper::White);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("Select an option (0-2): ", ConsoleHelper::Cyan, false);

                int weaponChoice = GameInput::GetValidatedChoice(0, 2);
                if (weaponChoice == 1)
                {
                    Weapon* primary = nullptr;
                    Weapon* secondary = nullptr;
                    {
                        WeaponManager manager;
                        manager.SelectPlayerLoadout(primary, secondary);
                    }
                    if (primary && secondary)
                    {
                        player->EquipWeapons(primary, secondary);
                        ConsoleHelper::print("\n[+] New weapons equipped successfully!", ConsoleHelper::Green);

                        std::string saveFileName = player->GetName() + "_save.txt";
                        player->SaveToFile(saveFileName);
                    }
                    ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);
                }
                else if (weaponChoice == 2)
                {
                    player->SwapWeapon();
                    ConsoleHelper::print("\n[+] Active weapon slot toggled successfully!", ConsoleHelper::Green);

                    std::string saveFileName = player->GetName() + "_save.txt";
                    player->SaveToFile(saveFileName);

                    ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);
                }
                else
                {
                    managingWeapons = false;
                }
            }
        }

        else if (choice == 3) // Open Inventory
        {
            InventoryScreen::Open(player);
        }

        else if (choice == 4) // Item Shop
        {
            ItemShop::Open(player);
        }

        else if (choice == 5) // Debug Menu
        {
            OpenDebugMenu(player);
        }

        else if (choice == 6) // Proceed to Boss Difficulty
        {
            preparing = false;
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
        ConsoleHelper::print("2. Add +1,000,000 XP (Level Up)", ConsoleHelper::White);
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
            player->GainXP(1000000);
            ConsoleHelper::print("\n[+] Added 1,000,000 XP!", ConsoleHelper::Green);
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
