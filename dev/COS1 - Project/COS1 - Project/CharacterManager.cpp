#include "CharacterManager.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <cstdlib>

Player* CharacterManager::CreateCharacter()
{
    system("cls");
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("     [ CHARACTER CREATION ]       ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Enter your character's name: ", ConsoleHelper::Cyan, false);

    std::string name;
    std::getline(std::cin, name);

    if (name.empty()) {
        name = "Hero";
    }

    // Create player with base stats and grant 30 unspent points for the Prep Hub
    Player* newPlayer = new Player(name);
    newPlayer->AddUnspentPoints(30);

    // Save initial state
    std::string saveFileName = name + "_save.txt";
    newPlayer->SaveToFile(saveFileName);

    system("cls");
    ConsoleHelper::print("\n========================================", ConsoleHelper::Green);
    ConsoleHelper::print("     [ CHARACTER CREATED SUCCESS! ]     ", ConsoleHelper::Green);
    ConsoleHelper::print("========================================", ConsoleHelper::Green);
    ConsoleHelper::print("\nEntering Preparation Hub...", ConsoleHelper::White);

    ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);

    return newPlayer;
}

// Function body for attribute allocation menu
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
