#include "Game.h"
#include <iostream>

Game::Game() : player(nullptr), currentBoss(nullptr), isRunning(true) {
}

Game::~Game() 
{
    delete player;
    delete currentBoss;
}

void Game::Initialize() 
{
    CharacterCreation();

    // Create starter weapons and boss
    Weapon* sword = new Weapon("Longsword", WeaponType::PureSTR, 15, 10, 0.8f, 0.2f, 0.0f, 0.0f, 15, 0, 10, 15);
    Weapon* staff = new Weapon("Flame Staff", WeaponType::PureINT, 20, 5, 0.0f, 0.0f, 1.0f, 0.0f, 10, 15, 5, 15);

    player->EquipWeapons(sword, staff);
    currentBoss = new Enemy("Relic Guardian", 200, 50);
}

void Game::CharacterCreation() 
{
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::cin >> playerName;
    player = new Player(playerName);
}

void Game::RenderUI() const 
{
    if (!player || !currentBoss) return;

    std::cout << "\n========================================\n";
    std::cout << "PLAYER: " << player->GetName() << " | HP: " << player->GetCurrentHP()
        << " | SP: " << player->GetCurrentSP() << " | MP: " << player->GetCurrentMP() << "\n";
    std::cout << "BOSS: " << currentBoss->GetName() << " | HP: " << currentBoss->GetCurrentHP()
        << " | Posture: " << currentBoss->GetCurrentPosture() << "\n";
    std::cout << "BOSS INTENT: " << currentBoss->GetIntentDescription() << "\n";
    std::cout << "========================================\n";
}

void Game::DisplayMenu() const 
{
    std::cout << "1. Light Attack\n";
    std::cout << "2. Heavy Attack\n";
    std::cout << "3. Swap Weapon\n";
    std::cout << "4. Block\n";
    std::cout << "5. Dodge\n";
    std::cout << "Choice: ";
}

void Game::RunCombatLoop() 
{
    while (isRunning && player->IsAlive() && currentBoss->IsAlive()) {
        currentBoss->GenerateIntent();
        RenderUI();
        DisplayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            player->PerformLightAttack(*currentBoss);
            break;
        case 2:
            player->PerformHeavyAttack(*currentBoss);
            break;
        case 3:
            player->SwapWeapon();
            break;
        case 4:
            player->Block();
            break;
        case 5:
            player->Dodge();
            break;
        default:
            std::cout << "Invalid action!\n";
            continue;
        }

        // Boss resolves action after player turn
        currentBoss->ExecuteIntent(*player);
        player->RegainResourcesPerTurn();
        currentBoss->ResetTurnState();
    }

    if (!player->IsAlive()) 
    {
        std::cout << "\nYou were defeated!\n";
    }
    else if (!currentBoss->IsAlive()) 
    {
        std::cout << "\nYou defeated the Relic Guardian!\n";
    }

    isRunning = false;
}