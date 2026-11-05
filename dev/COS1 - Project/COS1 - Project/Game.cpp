#include "Game.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include "WeaponManager.h"
#include <iostream>
#include <cstdlib>

Game::Game() : player(nullptr), currentBoss(nullptr), isRunning(true)
{
}

// Main Menu
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

    if (choice == 2)
    {
        LoadExistingGameSession();
    }
    else
    {
        StartFreshGameSession();
    }

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
            inWelcomeMenu = false; // Proceeds forward into character creation & game
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
            exit(0); // Clean exit
        }
    }
}

// Handle New Game
void Game::StartFreshGameSession()
{
    CharacterCreation();

    Weapon* primary = nullptr;
    Weapon* secondary = nullptr;
    {
        WeaponManager manager;
        manager.SelectPlayerLoadout(primary, secondary);
    }
    if (primary && secondary)
    {
        player->EquipWeapons(primary, secondary);
    }

    player->AddItem(new Item("Health Potion", ItemType::HealthPotion, 50, 20));
}

// Handle Load Game
void Game::LoadExistingGameSession()
{
    system("cls");
    ConsoleHelper::print("Enter your character's name to load: ", ConsoleHelper::Cyan, false);

    std::string charName;
    std::getline(std::cin, charName);

    if (charName.empty()) {
        charName = "Hero";
    }

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
        CharacterCreation();
    }

    // Updated to use WeaponManager instead of the deleted WeaponSelectionMenu()
    Weapon* primary = nullptr;
    Weapon* secondary = nullptr;
    {
        WeaponManager manager;
        manager.SelectPlayerLoadout(primary, secondary);
    }
    if (primary && secondary)
    {
        player->EquipWeapons(primary, secondary);
    }

    if (player->GetUnspentPoints() > 0)
    {
        AllocateAttributesMenu();
    }
}

// Character Creation Menu
void Game::CharacterCreation()
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
    player = new Player(playerName);

    // 2. Grant them their 30 starting attribute points to spend!
    player->AddUnspentPoints(30);

    // 3. Open the dedicated allocation menu
    AllocateAttributesMenu();

    system("cls");

    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("     [ ATTRIBUTES CONFIGURED! ]         ", ConsoleHelper::Cyan);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);
    player->DisplayStats();

    // Smooth transition message into weapon selection
    ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}

// Dedicated Attribute Allocation Menu
void Game::AllocateAttributesMenu()
{
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

// Set Boss Stats
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

// Difficulty Selection Menu
GameDifficulty Game::SelectDifficulty()
{
    return GameUI::SelectDifficulty();
}

// Combat Menu
void Game::DisplayMenu() const
{
    GameUI::DisplayCombatMenu();
}

// Combat Updates / Combat Loop
void Game::RunCombatLoop()
{
    bool rewardClaimed = false;

    while (true)
    {
        if (!player->IsAlive())
        {
            break;
        }

        system("cls");
        currentBoss->GenerateIntent();
        GameUI::RenderCombatUI(player, currentBoss);

        // --- TURN-BASED ACTION LOOP ---
        bool turnConsumed = false;

        while (!turnConsumed)
        {
            DisplayMenu(); // Displays Combat Menu
            int choice = GameInput::GetValidatedChoice(1, 7, 9);

            // Handle free actions vs turn-consuming actions
            if (choice == 3) // Swap Weapon (FREE)
            {
                player->SwapWeapon();
                ConsoleHelper::print("Swapped weapons!", ConsoleHelper::Green);
            }
            else if (choice == 6) // Inspect Weapons (FREE)
            {
                player->InspectWeapons();
            }
            else if (choice == 7) // Inventory Menu
            {
                const auto& inv = player->GetInventory();
                if (inv.empty())
                {
                    ConsoleHelper::print("\n[!] Your inventory is completely empty!", ConsoleHelper::Yellow);
                    ConsoleHelper::print("Returning to action selection...", ConsoleHelper::White);
                }
                else
                {
                    ConsoleHelper::print("\n==================================", ConsoleHelper::Cyan);
                    ConsoleHelper::print("          [ INVENTORY ]           ", ConsoleHelper::Cyan);
                    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                    for (size_t i = 0; i < inv.size(); ++i)
                    {
                        std::cout << i + 1 << ". ";
                        inv[i]->DisplayItemInfo();
                    }
                    ConsoleHelper::print("0. Back to Combat", ConsoleHelper::White);
                    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                    ConsoleHelper::print("Select item to use (0 to cancel): ", ConsoleHelper::Cyan, false);

                    int itemChoice = GameInput::GetValidatedChoice(0, (int)inv.size());
                    if (itemChoice > 0)
                    {
                        player->UseItem(itemChoice - 1);
                        turnConsumed = true; // Item used -> Turn consumed!
                    }
                }
            }
            else // Regular actions (Light Attack, Heavy Attack, Block, Dodge)
            {
                HandlePlayerAction(choice);
                turnConsumed = true; // Action executed -> Turn consumed!
            }
        }

        // --- CHECK IF BOSS DIED FROM PLAYER TURN ---
        if (!currentBoss->IsAlive())
        {
            system("cls");
            HandleCombatOutcome();

            if (!rewardClaimed && player->IsAlive())
            {
                rewardClaimed = true;
                int earnedXP = 150;
                if (currentDifficulty == GameDifficulty::Normal) earnedXP = 300;
                else if (currentDifficulty == GameDifficulty::Hard) earnedXP = 600;
                else if (currentDifficulty == GameDifficulty::Insane) earnedXP = 1200;
                else if (currentDifficulty == GameDifficulty::Impossible) earnedXP = 2400;

                ConsoleHelper::print("\n==================================", ConsoleHelper::Green);
                ConsoleHelper::print("         VICTORY REWARDS          ", ConsoleHelper::Green);
                ConsoleHelper::print("==================================", ConsoleHelper::Green);
                ConsoleHelper::print(" XP Earned: +" + std::to_string(earnedXP), ConsoleHelper::White);

                player->GainXP(earnedXP);

                std::string saveFileName = player->GetName() + "_save.txt";
                player->SaveToFile(saveFileName);

                ConsoleHelper::print("==================================", ConsoleHelper::Green);
            }

            // --- VICTORY MENU ---
            bool inVictoryMenu = true;
            while (inVictoryMenu)
            {
                ConsoleHelper::print("\n==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("        [ VICTORY OPTIONS ]       ", ConsoleHelper::Cyan);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("1. Review Current Stats & Attributes", ConsoleHelper::White);

                if (player->GetUnspentPoints() > 0)
                {
                    ConsoleHelper::print("2. Allocate Remaining Points (" + std::to_string(player->GetUnspentPoints()) + " left)", ConsoleHelper::Green);
                }
                else
                {
                    ConsoleHelper::print("2. Allocate Remaining Points [No Points Available]", ConsoleHelper::White);
                }

                ConsoleHelper::print("3. New Game", ConsoleHelper::White);
                ConsoleHelper::print("4. Main Menu (Select to Load Character and Play Again with Current Stats)", ConsoleHelper::White);
                ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                ConsoleHelper::print("Select an option (1-4): ", ConsoleHelper::Cyan, false);

                int victoryChoice = GameInput::GetValidatedChoice(1, 4);

                if (victoryChoice == 1) // Review Stats
                {
                    system("cls");
                    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                    ConsoleHelper::print("        [ CHARACTER STATS ]       ", ConsoleHelper::Cyan);
                    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
                    player->DisplayStats();
                    ConsoleHelper::print("\nPress Enter to return to victory menu...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);
                    system("cls");
                }
                else if (victoryChoice == 2) // Allocate Points
                {
                    if (player->GetUnspentPoints() > 0)
                    {
                        while (player->GetUnspentPoints() > 0)
                        {
                            AllocateAttributesMenu();
                        }

                        std::string saveFileName = player->GetName() + "_save.txt";
                        player->SaveToFile(saveFileName);
                        ConsoleHelper::print("[+] Attributes updated and saved!", ConsoleHelper::Green);
                    }
                    else
                    {
                        ConsoleHelper::print("\n[!] You have no unspent attribute points remaining!", ConsoleHelper::Yellow);
                    }

                    ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);
                    system("cls");
                }
                else if (victoryChoice == 3) // Play Again (Fresh Run)
                {
                    delete player;
                    player = nullptr;
                    delete currentBoss;
                    currentBoss = nullptr;

                    system("cls");
                    StartFreshGameSession();
                    SetupBossDifficulty();
                    RunCombatLoop();
                    return;
                }
                else if (victoryChoice == 4) // Exit to Main Menu
                {
                    delete player;
                    player = nullptr;
                    delete currentBoss;
                    currentBoss = nullptr;

                    system("cls");
                    DisplayWelcomeMenu();
                    Initialize();
                    RunCombatLoop();
                    return;
                }
            }
            break;
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
        system("cls");
        HandleCombatOutcome();
        if (std::cin.peek() == '\n') std::cin.ignore();
        ConsoleHelper::print("\nPress Enter to return to main menu...", ConsoleHelper::White, false);
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    isRunning = false;
}

// Player Turn Actions
void Game::HandlePlayerAction(int choice)
{
    Weapon* activeWeapon = player->GetActiveWeapon();

    switch (choice)
    {
    case 1: // Light Attack
    {
        std::string weaponName = activeWeapon->GetName();
        int damageDealt = player->PerformLightAttack(*currentBoss);

        if (weaponName != "Life Staff")
        {
            std::cout << " > You dealt " << damageDealt << " damage to " << currentBoss->GetName() << "!\n";
        }

        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp(), activeWeapon->GetBurnBuildUp(), activeWeapon->GetFrostbiteBuildUp());
        break;
    }
    case 2: // Heavy Attack
    {
        std::string weaponName = activeWeapon->GetName();
        int damageDealt = player->PerformHeavyAttack(*currentBoss);

        if (weaponName != "Life Staff")
        {
            std::cout << " > You landed a Heavy Attack for " << damageDealt << " damage!\n";
        }

        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp() * 2, activeWeapon->GetBurnBuildUp() * 2, activeWeapon->GetFrostbiteBuildUp() * 2);
        break;
    }
    case 4: // Block
        player->Block();
        ConsoleHelper::print("You raise your guard to block incoming damage.", ConsoleHelper::White);
        break;
    case 5: // Dodge
        player->Dodge();
        ConsoleHelper::print("You prepare to dodge the next attack.", ConsoleHelper::White);
        break;
    case 9: // Debug Insta-Kill ----------------------------------------------------------------------------------------------------------------------------
    {
        while (currentBoss->GetCurrentHP() > 0)
        {
            currentBoss->TakeDamage(99999999, 9999);
        }
        ConsoleHelper::print("[DEBUG] Relic Guardian obliterated!", ConsoleHelper::Yellow);
        break;
    }
    }
}

// Game End Screen
void Game::HandleCombatOutcome() const
{
    if (!player->IsAlive())
    {
        ConsoleHelper::print("=========================", ConsoleHelper::Red);
        ConsoleHelper::print("      [ You Died! ]      ", ConsoleHelper::Red);
        ConsoleHelper::print("=========================", ConsoleHelper::Red);
    }
    else if (!currentBoss->IsAlive())
    {
        ConsoleHelper::print("======================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("           Congratulations!           ", ConsoleHelper::Green);
        ConsoleHelper::print(" [ You defeated the Relic Guardian! ] ", ConsoleHelper::Cyan);
        ConsoleHelper::print("======================================", ConsoleHelper::Cyan);
    }
}

Game::~Game()
{
    delete player;
    delete currentBoss;
}
