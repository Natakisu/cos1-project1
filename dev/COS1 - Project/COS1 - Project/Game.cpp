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

void Game::CharacterCreation() {
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::cin >> playerName;
    player = new Player(playerName);

    int totalPoints = 30; // Points available to distribute
    int con = 10, str = 10, agi = 10, intel = 10, foc = 10; // Base values

    std::cout << "\n--- Character Creation ---\n";
    std::cout << "You have " << totalPoints << " bonus attribute points to distribute among CON, STR, AGI, INT, FOC.\n";

    int p;
    std::cout << "Add to Constitution (CON - increases HP): ";
    std::cin >> p; con += p; totalPoints -= p;

    std::cout << "Add to Strength (STR - increases heavy physical damage): ";
    std::cin >> p; str += p; totalPoints -= p;

    std::cout << "Add to Agility (AGI - increases stamina pools & light attacks): ";
    std::cin >> p; agi += p; totalPoints -= p;

    std::cout << "Add to Intellect (INT - increases mana pools & magic scaling): ";
    std::cin >> p; intel += p; totalPoints -= p;

    std::cout << "Add to Focus (FOC - increases support scaling): ";
    std::cin >> p; foc += p; totalPoints -= p;

    // Apply stats to the player
    player->SetAttributes(con, str, agi, intel, foc);
    player->DisplayStats();
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
    std::cout << "6. Inspect Weapons\n";
    std::cout << "Choice: ";
}

void Game::RunCombatLoop() {
    while (isRunning && player->IsAlive() && currentBoss->IsAlive()) {
        currentBoss->GenerateIntent();
        RenderUI();
        DisplayMenu();

        int choice = 0;
        std::cout << "Choice: ";
        std::cin >> choice;

        // Update validation range
        while (std::cin.fail() || choice < 1 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "[!] Invalid input. Please enter a number between 1 and 6: ";
            std::cin >> choice;
        }

        switch (choice) {
        case 1:
            player->PerformLightAttack(*currentBoss);
            break;
        case 2:
            player->PerformHeavyAttack(*currentBoss);
            break;
        case 3:
            player->SwapWeapon();
            std::cout << "Swapped weapons!\n";
            continue; // Free action / check stats.
        case 4:
            player->Block();
            break;
        case 5:
            player->Dodge();
            break;
        case 6:
            player->InspectWeapons();
            continue; // Inspecting weapons doesn't use up the turn.
        default:
            continue;
        }

        // Boss resolves action after player turn
        currentBoss->ExecuteIntent(*player);
        player->RegainResourcesPerTurn();
        currentBoss->ResetTurnState();
    }

    if (!player->IsAlive()) {
        std::cout << "\nYou were defeated!\n";
    }
    else if (!currentBoss->IsAlive()) {
        std::cout << "\nYou defeated the Relic Guardian!\n";
    }

    isRunning = false;
}