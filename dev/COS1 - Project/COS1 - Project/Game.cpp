#include "Game.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include "WeaponManager.h"
#include "CharacterManager.h"
#include "PreparationMenu.h"
#include <iostream>
#include <cstdlib>

Game::Game() : player(nullptr), currentBoss(nullptr), isRunning(true)
{
}

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
            int choice = GameInput::GetValidatedChoice(1, 8, 9);

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
                turnConsumed = HandleInventoryMenu();
            }
            else if (choice == 8) // Weapon Skills Menu
            {
                turnConsumed = HandleWeaponSkillMenu();
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
            HandleCombatOutcome();

            if (!rewardClaimed && player->IsAlive())
            {
                rewardClaimed = true;
                HandleVictoryRewards();
            }

            if (!HandleVictoryMenu()) break;
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
        HandleDeathMenu();
    }
}

// --- SUB-HANDLERS & MENU EXTRACTIONS ---

bool Game::HandleInventoryMenu()
{
    const auto& inv = player->GetInventory();
    if (inv.empty())
    {
        ConsoleHelper::print("\n[!] Your inventory is completely empty!", ConsoleHelper::Yellow);
        return false;
    }

    ConsoleHelper::print("\n==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("          [ INVENTORY ]           ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    for (size_t i = 0; i < inv.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        inv[i]->DisplayInfo();
    }
    ConsoleHelper::print("0. Back to Combat", ConsoleHelper::White);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Select item/spell to use (0 to cancel): ", ConsoleHelper::Cyan, false);

    int itemChoice = GameInput::GetValidatedChoice(0, (int)inv.size());
    if (itemChoice == 0) return false;

    Item* chosenItem = inv[itemChoice - 1];
    ItemType type = chosenItem->GetType();

    if (type == ItemType::DinsFire || type == ItemType::FaroresWind || type == ItemType::NayrusLove)
    {
        if (player->GetCurrentMP() < 100)
        {
            ConsoleHelper::print("\n[!] Not enough Mana to cast " + chosenItem->GetName() + "! (Requires 100 MP)", ConsoleHelper::Red);
            return false;
        }
        player->ConsumeMP(100);

        if (type == ItemType::DinsFire)
        {
            currentBoss->TakeDamage(45, 15);
            currentBoss->ApplyStatusBuildup(0, 75, 0);
            ConsoleHelper::print("\n > You cast Din's Fire! Intense Burn applied.", ConsoleHelper::Red);
        }
        else if (type == ItemType::FaroresWind)
        {
            currentBoss->TakeDamage(35, 20);
            currentBoss->ApplyStatusBuildup(75, 0, 0);
            ConsoleHelper::print("\n > You cast Farore's Wind! Severe Bleed applied.", ConsoleHelper::Green);
        }
        else if (type == ItemType::NayrusLove)
        {
            currentBoss->TakeDamage(35, 25);
            currentBoss->ApplyStatusBuildup(0, 0, 75);
            ConsoleHelper::print("\n > You cast Nayru's Love! Heavy Frostbite applied.", ConsoleHelper::Cyan);
        }
    }
    else
    {
        player->UseItem(itemChoice - 1);
    }
    return true;
}

bool Game::HandleWeaponSkillMenu()
{
    Weapon* activeWeapon = player->GetActiveWeapon();
    if (!activeWeapon)
    {
        ConsoleHelper::print("\n[!] No active weapon equipped!", ConsoleHelper::Red);
        return false;
    }

    system("cls");
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("             [ WEAPON SKILLS: " + activeWeapon->GetName() + " ]       ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);

    int shortCD = activeWeapon->GetShortCooldownRemaining();
    int longCD = activeWeapon->GetLongCooldownRemaining();

    std::cout << "1. Short Skill";
    if (shortCD == 0) ConsoleHelper::print(" [READY]", ConsoleHelper::Green);
    else std::cout << " [CD: " << shortCD << " turns]\n";

    std::cout << "2. Long Skill";
    if (longCD == 0) ConsoleHelper::print(" [READY]", ConsoleHelper::Green);
    else std::cout << " [CD: " << longCD << " turns]\n";

    ConsoleHelper::print("0. Back", ConsoleHelper::White);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Select skill (0-2): ", ConsoleHelper::Cyan, false);

    int skillChoice = GameInput::GetValidatedChoice(0, 2);
    if (skillChoice == 0) return false;

    bool isLong = (skillChoice == 2);
    bool success = player->ExecuteWeaponSkill(isLong, *currentBoss);

    if (success)
    {
        if (std::cin.peek() == '\n') std::cin.ignore();
        ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::Cyan, false);
        std::string dummy;
        std::getline(std::cin, dummy);
    }
    return success;
}

void Game::HandleVictoryRewards()
{
    int earnedXP = 150;
    if (currentDifficulty == GameDifficulty::Normal) earnedXP = 300;
    else if (currentDifficulty == GameDifficulty::Hard) earnedXP = 600;
    else if (currentDifficulty == GameDifficulty::Insane) earnedXP = 1200;
    else if (currentDifficulty == GameDifficulty::Impossible) earnedXP = 2400;

    int earnedShards = 100;
    if (currentDifficulty == GameDifficulty::Normal) earnedShards = 200;
    else if (currentDifficulty == GameDifficulty::Hard) earnedShards = 300;
    else if (currentDifficulty == GameDifficulty::Insane) earnedShards = 400;
    else if (currentDifficulty == GameDifficulty::Impossible) earnedShards = 500;

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

bool Game::HandleVictoryMenu()
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
            SetupBossDifficulty();
            return true;
        }
        else if (choice == 4)
        {
            player->AutoSave();
            delete player; player = nullptr;
            delete currentBoss; currentBoss = nullptr;
            system("cls");
            DisplayWelcomeMenu();
            Initialize();
            RunCombatLoop();
            return false;
        }
        else if (choice == 5)
        {
            player->AutoSave();
            delete player; player = nullptr;
            delete currentBoss; currentBoss = nullptr;
            isRunning = false;
            return false;
        }
    }
}

void Game::HandleDeathMenu()
{
    system("cls");
    HandleCombatOutcome();
    ConsoleHelper::print("\n==================================", ConsoleHelper::Red);
    ConsoleHelper::print("1. Load Last Save", ConsoleHelper::White);
    ConsoleHelper::print("2. Return to Main Menu", ConsoleHelper::White);
    ConsoleHelper::print("==================================", ConsoleHelper::Red);
    ConsoleHelper::print("Select an option (1-2): ", ConsoleHelper::Cyan, false);

    int choice = GameInput::GetValidatedChoice(1, 2);
    if (choice == 1)
    {
        player->LoadFromFile(player->GetName() + "_save.txt");
        SetupBossDifficulty();
        RunCombatLoop();
    }
    else
    {
        delete player; player = nullptr;
        delete currentBoss; currentBoss = nullptr;
        system("cls");
        DisplayWelcomeMenu();
        Initialize();
        RunCombatLoop();
    }
}

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

void Game::HandleCombatOutcome() const
{
    if (!player->IsAlive())
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

Game::~Game()
{
    delete player;
    delete currentBoss;
}