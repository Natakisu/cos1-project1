#include "Game.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include "WeaponManager.h"
#include "CharacterManager.h"
#include "PreparationMenu.h"
#include "GameProgression.h"
#include "CombatMenuManager.h"
#include <iostream>
#include <cstdlib>

// --- CONSTRUCTORS & DESTRUCTOR ---
Game::Game() : player(nullptr), currentBoss(nullptr), isRunning(true) {}

Game::~Game()
{
    delete player;
    delete currentBoss;
}

// --- INITIALIZATION & SESSION MANAGEMENT ---
void Game::Initialize()
{
    isRunning = true;
    system("cls");
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("        [ RELIC SWITCHER ]        ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("1. New Game", ConsoleHelper::White);
    ConsoleHelper::print("2. Load Saved Game", ConsoleHelper::White);

    int choice = GameInput::GetValidatedChoice(1, 2);
    if (choice == 2) LoadExistingGameSession();
    else StartFreshGameSession();

    SetupBossDifficulty();
}

void Game::DisplayWelcomeMenu()
{
    bool inWelcomeMenu = true;
    while (inWelcomeMenu)
    {
        GameUI::DisplayWelcomeMenu();
        int choice = GameInput::GetValidatedChoice(1, 3);
        if (choice == 1)
        {
            inWelcomeMenu = false;
        }
        else if (choice == 2)
        {
            GameUI::DisplayInstructions();
            ConsoleHelper::print("Press Enter to return to the main menu...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 3)
        {
            ConsoleHelper::print("\nExiting game. Thanks for playing!", ConsoleHelper::Green);
            exit(0);
        }
    }
}

void Game::StartFreshGameSession()
{
    player = CharacterManager::CreateCharacter();
    player->AddItem(new Item("Health Potion", ItemType::HealthPotion, 50, 20));
    PreparationMenu::Open(player);
}

void Game::LoadExistingGameSession()
{
    system("cls");
    ConsoleHelper::print("Enter your character's name to load: ", ConsoleHelper::Cyan, false);

    std::string charName;
    std::getline(std::cin, charName);
    if (charName.empty()) charName = "Hero";

    std::string saveFileName = charName + "_save.txt";
    player = new Player(charName);
    player->LoadFromFile(saveFileName);

    if (player->GetLevel() <= 0 && player->GetMaxHP() <= 100)
    {
        ConsoleHelper::print("\n[!] Could not find save file: " + saveFileName, ConsoleHelper::Red);
        ConsoleHelper::print("Starting fresh character creation instead...", ConsoleHelper::Yellow);
        ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
        std::string dummy;
        std::getline(std::cin, dummy);

        delete player;
        player = CharacterManager::CreateCharacter();
    }
    PreparationMenu::Open(player);
}

void Game::SetupBossDifficulty()
{
    currentDifficulty = GameUI::SelectDifficulty();
    int bossHP = 5000;
    if (currentDifficulty == GameDifficulty::Easy) bossHP = 500;
    else if (currentDifficulty == GameDifficulty::Normal) bossHP = 5000;
    else if (currentDifficulty == GameDifficulty::Hard) bossHP = 50000;
    else if (currentDifficulty == GameDifficulty::Insane) bossHP = 500000;
    else if (currentDifficulty == GameDifficulty::Impossible) bossHP = 5000000;

    delete currentBoss;
    currentBoss = new Enemy("Relic Guardian", bossHP, 50, currentDifficulty);
}

// --- CORE COMBAT LOOP ---
void Game::RunCombatLoop()
{
    bool rewardClaimed = false;

    while (true)
    {
        if (!player->IsAlive()) break;

        system("cls");
        currentBoss->GenerateIntent();

        if (player->GetActiveWeapon())
        {
            player->GetActiveWeapon()->UpdateCooldowns();
        }

        GameUI::RenderCombatUI(player, currentBoss);

        bool turnConsumed = false;
        while (!turnConsumed)
        {
            GameUI::DisplayCombatMenu();
            int choice = GameInput::GetValidatedChoice(1, 9);

            if (choice == 3) // Swap Weapon (Free)
            {
                player->SwapWeapon();
                ConsoleHelper::print("Swapped weapons!", ConsoleHelper::Green);
            }
            else if (choice == 6) // Inspect Weapons (Free)
            {
                player->InspectWeapons();
            }
            else if (choice == 7) // Inventory & Magic Spells
            {
                turnConsumed = CombatMenuManager::HandleInventoryMenu(player, currentBoss);
            }
            else if (choice == 8) // Weapon Skills Menu
            {
                turnConsumed = CombatMenuManager::HandleWeaponSkillMenu(player, currentBoss);
            }
            else // Regular Combat Actions
            {
                HandlePlayerAction(choice);
                turnConsumed = true;
            }
        }

        // --- CHECK VICTORY ---
        if (!currentBoss->IsAlive())
        {
            system("cls");
            GameProgression::DisplayCombatOutcome(true);

            if (!rewardClaimed && player->IsAlive())
            {
                rewardClaimed = true;
                GameProgression::HandleVictoryRewards(player, currentDifficulty);
            }

            if (!GameProgression::HandleVictoryMenu(player, *this, isRunning)) break;
            return;
        }

        // --- BOSS TURN ---
        currentBoss->ResolveStatusEffects();
        if (!currentBoss->IsAlive()) continue;

        currentBoss->ExecuteIntent(*player);
        if (!player->IsAlive()) break;

        if (std::cin.peek() == '\n') std::cin.ignore();
        ConsoleHelper::print("\n[Turn Complete] Press Enter to continue...", ConsoleHelper::Cyan, false);
        std::string pauseInput;
        std::getline(std::cin, pauseInput);

        player->RegainResourcesPerTurn();
        currentBoss->ResetTurnState();
    }

    if (!player->IsAlive())
    {
        GameProgression::HandleDeathMenu(player, *this);
    }
}

// --- PLAYER ACTIONS ---
void Game::HandlePlayerAction(int choice)
{
    Weapon* activeWeapon = player->GetActiveWeapon();
    switch (choice)
    {
    case 1:
    {
        int dmg = player->PerformLightAttack(*currentBoss);
        if (activeWeapon->GetName() != "Life Staff")
            std::cout << " > You dealt " << dmg << " damage!\n";
        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp(), activeWeapon->GetBurnBuildUp(), activeWeapon->GetFrostbiteBuildUp());
        break;
    }
    case 2:
    {
        int dmg = player->PerformHeavyAttack(*currentBoss);
        if (activeWeapon->GetName() != "Life Staff")
            std::cout << " > You landed a Heavy Attack for " << dmg << " damage!\n";
        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp() * 2, activeWeapon->GetBurnBuildUp() * 2, activeWeapon->GetFrostbiteBuildUp() * 2);
        break;
    }
    case 4:
        player->Block();
        ConsoleHelper::print("You raise your guard.", ConsoleHelper::White);
        break;
    case 5:
        player->Dodge();
        ConsoleHelper::print("You prepare to dodge.", ConsoleHelper::White);
        break;
    case 9:
        while (currentBoss->GetCurrentHP() > 0) currentBoss->TakeDamage(9999999, 9999);
        ConsoleHelper::print("[DEBUG] Relic Guardian obliterated!", ConsoleHelper::Yellow);
        break;
    }
}
