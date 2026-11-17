#include "GameProgression.h"
#include "Game.h" 
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include "CharacterManager.h"
#include "PreparationMenu.h"
#include <iostream>
#include <cstdlib>

// --- VICTORY REWARDS & PROGRESSION ---
void GameProgression::HandleVictoryRewards(Player* player, GameDifficulty difficulty)
{
    int earnedXP = 150;
    if (difficulty == GameDifficulty::Normal) earnedXP = 300;
    else if (difficulty == GameDifficulty::Hard) earnedXP = 600;
    else if (difficulty == GameDifficulty::Insane) earnedXP = 1200;
    else if (difficulty == GameDifficulty::Impossible) earnedXP = 2400;

    int earnedShards = 100;
    if (difficulty == GameDifficulty::Normal) earnedShards = 200;
    else if (difficulty == GameDifficulty::Hard) earnedShards = 300;
    else if (difficulty == GameDifficulty::Insane) earnedShards = 400;
    else if (difficulty == GameDifficulty::Impossible) earnedShards = 500;

    ConsoleHelper::print("\n==================================", ConsoleHelper::Green);
    ConsoleHelper::print("         VICTORY REWARDS          ", ConsoleHelper::Green);
    ConsoleHelper::print("==================================", ConsoleHelper::Green);
    ConsoleHelper::print(" XP Earned: +" + std::to_string(earnedXP), ConsoleHelper::Cyan);
    ConsoleHelper::print(" Relic Shards Earned: +" + std::to_string(earnedShards) + "rs", ConsoleHelper::Purple);

    player->GainXP(earnedXP);
    player->AddRelicShards(earnedShards);
    player->AutoSave();
    ConsoleHelper::print("==================================", ConsoleHelper::Green);
}

// --- VICTORY & DEATH MENUS ---
bool GameProgression::HandleVictoryMenu(Player* player, Game& gameRef, bool& isRunning)
{
    while (true)
    {
        ConsoleHelper::print("\n==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("        [ VICTORY OPTIONS ]       ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Review Stats", ConsoleHelper::White);
        ConsoleHelper::print("2. Allocate Points (" + std::to_string(player->GetUnspentPoints()) + " left)", ConsoleHelper::Green);
        ConsoleHelper::print("3. Return to Prep Hub", ConsoleHelper::White);
        ConsoleHelper::print("4. Main Menu", ConsoleHelper::White);
        ConsoleHelper::print("5. Exit Game", ConsoleHelper::White);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option (1-5): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(1, 5);
        if (choice == 1)
        {
            player->DisplayStats();
        }
        else if (choice == 2)
        {
            while (player->GetUnspentPoints() > 0)
            {
                CharacterManager::RunAttributeAllocationMenu(player);
            }
            player->AutoSave();
            ConsoleHelper::print("[+] Attributes updated and saved!", ConsoleHelper::Green);
        }
        else if (choice == 3)
        {
            player->AutoSave();
            system("cls");
            PreparationMenu::Open(player);
            gameRef.SetupBossDifficulty();
            return true;
        }
        else if (choice == 4)
        {
            player->AutoSave();
            system("cls");
            gameRef.DisplayWelcomeMenu();
            gameRef.Initialize();
            gameRef.RunCombatLoop();
            return false;
        }
        else if (choice == 5)
        {
            player->AutoSave();
            isRunning = false;
            return false;
        }
    }
}

void GameProgression::HandleDeathMenu(Player* player, Game& gameRef)
{
    system("cls");
    DisplayCombatOutcome(false);
    ConsoleHelper::print("\n==================================", ConsoleHelper::Red);
    ConsoleHelper::print("1. Load Last Save", ConsoleHelper::White);
    ConsoleHelper::print("2. Return to Main Menu", ConsoleHelper::White);
    ConsoleHelper::print("==================================", ConsoleHelper::Red);
    ConsoleHelper::print("Select an option (1-2): ", ConsoleHelper::Cyan, false);

    int choice = GameInput::GetValidatedChoice(1, 2);
    if (choice == 1)
    {
        player->LoadFromFile(player->GetName() + "_save.txt");
        gameRef.SetupBossDifficulty();
        gameRef.RunCombatLoop();
    }
    else
    {
        system("cls");
        gameRef.DisplayWelcomeMenu();
        gameRef.Initialize();
        gameRef.RunCombatLoop();
    }
}

void GameProgression::DisplayCombatOutcome(bool isPlayerAlive)
{
    if (!isPlayerAlive)
    {
        ConsoleHelper::print("=========================", ConsoleHelper::Red);
        ConsoleHelper::print("      [ You Died! ]      ", ConsoleHelper::Red);
        ConsoleHelper::print("=========================", ConsoleHelper::Red);
    }
    else
    {
        ConsoleHelper::print("======================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("           Congratulations!           ", ConsoleHelper::Green);
        ConsoleHelper::print(" [ You defeated the Relic Guardian! ] ", ConsoleHelper::Cyan);
        ConsoleHelper::print("======================================", ConsoleHelper::Cyan);
    }
}
