#include "CharacterManager.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <cstdlib>

Player* CharacterManager::CreateCharacter()
{
    std::string playerName;
    bool validName = false;

    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("        [ CHARACTER CREATION ]          ", ConsoleHelper::Cyan);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);

    // Keep prompting until a valid, non-empty name is entered
    while (!validName)
    {
        ConsoleHelper::print("Enter your character's name: ", ConsoleHelper::Cyan, false);
        std::getline(std::cin, playerName);

        if (playerName.empty() || playerName.find_first_not_of(' ') == std::string::npos)
        {
            ConsoleHelper::print("[!] Name cannot be empty. Please enter a valid name.", ConsoleHelper::Yellow);
        }
        else
        {
            validName = true;
        }
    }

    // 1. Create player
    Player* newPlayer = new Player(playerName);

    // 2. Grant them their 30 starting attribute points to spend!
    newPlayer->AddUnspentPoints(30);

    // 3. Open the dedicated allocation menu
    RunAttributeAllocationMenu(newPlayer);

    system("cls");

    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("     [ ATTRIBUTES CONFIGURED! ]         ", ConsoleHelper::Cyan);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);
    newPlayer->DisplayStats();

    // Smooth transition message
    ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);

    return newPlayer;
}

void CharacterManager::RunAttributeAllocationMenu(Player* player)
{
    if (!player) return;

    GameUI::DisplayAttributeDescriptions();
    ConsoleHelper::print("\nPress Enter to begin attribute allocation...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);

    while (player->GetUnspentPoints() > 0)
    {
        system("cls");
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("       ALLOCATE ATTRIBUTES        ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Unspent Points: " + std::to_string(player->GetUnspentPoints()), ConsoleHelper::Green);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Constitution (CON)", ConsoleHelper::White);
        ConsoleHelper::print("2. Strength (STR)", ConsoleHelper::White);
        ConsoleHelper::print("3. Agility (AGI)", ConsoleHelper::White);
        ConsoleHelper::print("4. Intellect (INT)", ConsoleHelper::White);
        ConsoleHelper::print("5. Focus (FOC)", ConsoleHelper::White);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select attribute to upgrade (1-5): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(1, 5);

        ConsoleHelper::print("Enter points to allocate: ", ConsoleHelper::White, false);
        int amount = GameInput::GetValidatedChoice(1, player->GetUnspentPoints());

        if (amount > 0 && amount <= player->GetUnspentPoints())
        {
            player->AllocateAttribute(choice, amount);
            player->UpdateDerivedStats();
        }
        else
        {
            ConsoleHelper::print("[!] Invalid amount. Press Enter to continue...", ConsoleHelper::Red, false);
            std::string errDummy;
            std::getline(std::cin, errDummy);
        }
    }
}
