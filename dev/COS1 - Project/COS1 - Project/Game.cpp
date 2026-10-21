#include "Game.h"
#include "GameUI.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <cstdlib>

Game::Game() : player(nullptr), currentBoss(nullptr), isRunning(true)
{
}

Game::~Game()
{
    delete player;
    delete currentBoss;
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
        player = new Player("Hero");
        player->LoadFromFile("savegame.txt");
        WeaponSelectionMenu();

        // If they have unspent points saved over, let them allocate them!
        if (player->GetUnspentPoints() > 0)
        {
            AllocateAttributesMenu();
        }
    }
    else
    {
        // Fresh start
        CharacterCreation();
        WeaponSelectionMenu();
    }

    currentDifficulty = GameUI::SelectDifficulty();

    int bossHP = 5000;
    if (currentDifficulty == GameDifficulty::Easy) bossHP = 500;
    else if (currentDifficulty == GameDifficulty::Normal) bossHP = 5000;
    else if (currentDifficulty == GameDifficulty::Hard) bossHP = 50000;
    else if (currentDifficulty == GameDifficulty::Insane) bossHP = 500000;
    else if (currentDifficulty == GameDifficulty::Impossible) bossHP = 5000000;

    currentBoss = new Enemy("Relic Guardian", bossHP, 50, currentDifficulty);
}

// Character Creation Menu
void Game::CharacterCreation()
{
    std::string playerName;
    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("        [ CHARACTER CREATION ]          ", ConsoleHelper::Cyan);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Enter your character's name: ", ConsoleHelper::Cyan, false);
    std::getline(std::cin, playerName);

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
}

// Dedicated Attribute Allocation Menu (Reusable for New Game & Level Ups/Loads)
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

// Combat Action Menu
void Game::DisplayMenu() const
{
    GameUI::DisplayCombatMenu();
}

// Weapon Swap and Healing
void Game::HandlePlayerAction(int choice)
{
    Weapon* activeWeapon = player->GetActiveWeapon();

    switch (choice)
    {
    case 1:
    {
        std::string weaponName = activeWeapon->GetName();
        int damageDealt = player->PerformLightAttack(*currentBoss);

        if (weaponName != "Life Staff")
        {
            std::cout << " > You dealt " << damageDealt << " damage to " << currentBoss->GetName() << "!\n";
        }

        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp(), activeWeapon->GetBurnBuildUp(), 0);
        break;
    }
    case 2:
    {
        std::string weaponName = activeWeapon->GetName();
        int damageDealt = player->PerformHeavyAttack(*currentBoss);

        if (weaponName != "Life Staff")
        {
            std::cout << " > You landed a Heavy Attack for " << damageDealt << " damage!\n";
        }

        currentBoss->ApplyStatusBuildup(activeWeapon->GetBleedBuildUp() * 2, activeWeapon->GetBurnBuildUp() * 2, 0);
        break;
    }
    case 3:
        player->SwapWeapon();
        ConsoleHelper::print("Swapped weapons!", ConsoleHelper::Green);
        break;
    case 4:
        player->Block();
        ConsoleHelper::print("You raise your guard to block incoming damage.", ConsoleHelper::White);
        break;
    case 5:
        player->Dodge();
        ConsoleHelper::print("You prepare to dodge the next attack.", ConsoleHelper::White);
        break;
    case 6:
        player->InspectWeapons();
        break;
    case 9:
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

                if (player->GetUnspentPoints() > 0)
                {
                    if (std::cin.peek() == '\n') std::cin.ignore();
                    ConsoleHelper::print("\nPress Enter to allocate your attribute points...", ConsoleHelper::White, false);
                    std::string dummy;
                    std::getline(std::cin, dummy);

                    while (player->GetUnspentPoints() > 0)
                    {
                        AllocateAttributesMenu();
                    }
                }

                player->SaveToFile("savegame.txt");

                ConsoleHelper::print("==================================", ConsoleHelper::Green);
            }

            if (std::cin.peek() == '\n') std::cin.ignore();
            ConsoleHelper::print("\nPress Enter to return to main menu...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
            break;
        }

        system("cls");
        currentBoss->GenerateIntent();
        GameUI::RenderCombatUI(player, currentBoss);
        DisplayMenu();

        int choice = GameInput::GetValidatedChoice(1, 6, 9);
        HandlePlayerAction(choice);

        if (choice == 6 || choice == 3)
        {
            if (std::cin.peek() == '\n') std::cin.ignore();
            ConsoleHelper::print("\nPress Enter to return to combat...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }

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

// Creates Weapons
void Game::InitializeWeaponPool()
{
    availableWeapons.push_back(new Weapon("Warhammer", WeaponType::PureSTR, 25, 18, 1.0f, 0.0f, 0.0f, 0.0f, 25, 0, 20, 25, 0, 0));
    availableWeapons.push_back(new Weapon("Sword and Shield", WeaponType::PureSTR, 15, 10, 0.8f, 0.2f, 0.0f, 0.0f, 12, 5, 15, 18, 0, 0));

    availableWeapons.push_back(new Weapon("Daggers", WeaponType::PureAGI, 10, 6, 0.2f, 0.8f, 0.0f, 0.0f, 8, 0, 8, 10, 35, 0));
    availableWeapons.push_back(new Weapon("Bow", WeaponType::PureAGI, 14, 8, 0.1f, 0.9f, 0.0f, 0.0f, 10, 0, 10, 12, 0, 0));

    availableWeapons.push_back(new Weapon("Fire Staff", WeaponType::PureINT, 20, 5, 0.0f, 0.0f, 1.0f, 0.0f, 10, 15, 5, 15, 0, 40));
    availableWeapons.push_back(new Weapon("Ice Staff", WeaponType::PureINT, 16, 6, 0.0f, 0.0f, 0.9f, 0.1f, 8, 16, 6, 12, 0, 0));

    availableWeapons.push_back(new Weapon("Life Staff", WeaponType::PureFOC, 12, 4, 0.0f, 0.0f, 0.0f, 1.0f, 6, 12, 10, 15, 0, 0));

    availableWeapons.push_back(new Weapon("Greatsword", WeaponType::Hybrid, 22, 14, 0.5f, 0.5f, 0.0f, 0.0f, 20, 0, 15, 20, 0, 0));
    availableWeapons.push_back(new Weapon("Rapier", WeaponType::Hybrid, 13, 7, 0.2f, 0.4f, 0.4f, 0.0f, 9, 8, 7, 12, 0, 0));
    availableWeapons.push_back(new Weapon("Flail and Shield", WeaponType::Hybrid, 17, 12, 0.4f, 0.0f, 0.0f, 0.6f, 15, 8, 14, 18, 0, 0));
}

// Weapon Menu
void Game::WeaponSelectionMenu()
{
    bool weaponsConfirmed = false;

    InitializeWeaponPool();

    Weapon* chosenPrimary = nullptr;
    Weapon* chosenSecondary = nullptr;

    while (!weaponsConfirmed)
    {
        ConsoleHelper::print("\n==================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("              [ WEAPON SELECTION MENU ]           ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print(" Current Loadout:", ConsoleHelper::White);
        std::cout << "  - Primary:   " << (chosenPrimary ? chosenPrimary->GetName() : "[None Selected]") << "\n";
        std::cout << "  - Secondary: " << (chosenSecondary ? chosenSecondary->GetName() : "[None Selected]") << "\n";
        ConsoleHelper::print("--------------------------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print(" Select a Weapon Scaling Category:", ConsoleHelper::White);
        ConsoleHelper::print("  1. [STR] Strength Weapons", ConsoleHelper::White);
        ConsoleHelper::print("  2. [AGI] Agility Weapons", ConsoleHelper::White);
        ConsoleHelper::print("  3. [INT] Intellect Weapons", ConsoleHelper::White);
        ConsoleHelper::print("  4. [FOC] Focus Weapons", ConsoleHelper::White);
        ConsoleHelper::print("  5. [HYB] Hybrid Weapons", ConsoleHelper::White);

        std::cout << "  6. [ALL] View All Weapons ";
        ConsoleHelper::print("[WARNING]: This will Word Bomb your console", ConsoleHelper::Red);

        if (chosenPrimary != nullptr && chosenSecondary != nullptr)
        {
            ConsoleHelper::print("  7. [OK]  Finish & Confirm Loadout", ConsoleHelper::Green);
        }

        ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
        int maxOption = (chosenPrimary && chosenSecondary) ? 7 : 6;
        int categoryChoice = GameInput::GetValidatedChoice(1, maxOption);

        if (categoryChoice == 7 && chosenPrimary != nullptr && chosenSecondary != nullptr)
        {
            weaponsConfirmed = true;
            break;
        }

        std::vector<Weapon*> filteredWeapons;
        for (Weapon* w : availableWeapons)
        {
            WeaponType type = w->GetType();
            if (categoryChoice == 1 && type == WeaponType::PureSTR) filteredWeapons.push_back(w);
            else if (categoryChoice == 2 && type == WeaponType::PureAGI) filteredWeapons.push_back(w);
            else if (categoryChoice == 3 && type == WeaponType::PureINT) filteredWeapons.push_back(w);
            else if (categoryChoice == 4 && type == WeaponType::PureFOC) filteredWeapons.push_back(w);
            else if (categoryChoice == 5 && type == WeaponType::Hybrid) filteredWeapons.push_back(w);
        }

        if (categoryChoice == 6 || filteredWeapons.empty())
        {
            filteredWeapons = availableWeapons;
        }

        ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("       [ AVAILABLE WEAPONS IN GROUP ]   ", ConsoleHelper::Cyan);
        ConsoleHelper::print("========================================", ConsoleHelper::Cyan);

        for (size_t i = 0; i < filteredWeapons.size(); ++i)
        {
            std::cout << i + 1 << ". ";
            filteredWeapons[i]->DisplayWeaponInfo();

            std::string name = filteredWeapons[i]->GetName();
            std::cout << "   -> Identity: ";
            if (name == "Warhammer")
                ConsoleHelper::print("Slower attack speed, high physical damage, massive posture damage.", ConsoleHelper::White);
            else if (name == "Sword and Shield")
                ConsoleHelper::print("Balanced offensive/defensive with high block stability.", ConsoleHelper::White);
            else if (name == "Daggers")
                ConsoleHelper::print("Fast attack speed, multi-hits, rapid Bleed buildup.", ConsoleHelper::White);
            else if (name == "Bow")
                ConsoleHelper::print("Ranged physical damage; quick shots or aimed high damage.", ConsoleHelper::White);
            else if (name == "Fire Staff")
                ConsoleHelper::print("High magic damage with Burn status buildup (damage over time).", ConsoleHelper::White);
            else if (name == "Ice Staff")
                ConsoleHelper::print("Control & mitigation; reduces enemy stamina regeneration.", ConsoleHelper::White);
            else if (name == "Life Staff")
                ConsoleHelper::print("Support: Can heal the user instead of attacking.", ConsoleHelper::White);
            else if (name == "Greatsword")
                ConsoleHelper::print("Hybrid: Heavy attacks scale with STR; light multi-hits scale with AGI.", ConsoleHelper::White);
            else if (name == "Rapier")
                ConsoleHelper::print("Hybrid: Finesse weapon with cross-resource detonation (Bleed/Burn).", ConsoleHelper::White);
            else if (name == "Flail and Shield")
                ConsoleHelper::print("Hybrid: Heals on attack if Focus is 12 or higher.", ConsoleHelper::White);
            else
                ConsoleHelper::print("Standard combat weapon.", ConsoleHelper::White);

            ConsoleHelper::print("----------------------------------------", ConsoleHelper::Cyan);
        }

        ConsoleHelper::print("Enter 0 to go back to category menu without picking.", ConsoleHelper::White);
        int weaponChoice = GameInput::GetValidatedChoice(0, (int)filteredWeapons.size());

        if (weaponChoice > 0 && weaponChoice <= (int)filteredWeapons.size())
        {
            Weapon* selected = filteredWeapons[weaponChoice - 1];

            std::cout << "\nAssign " << selected->GetName() << " to:\n";
            ConsoleHelper::print("1. Primary Slot", ConsoleHelper::White);
            ConsoleHelper::print("2. Secondary Slot", ConsoleHelper::White);
            int slotChoice = GameInput::GetValidatedChoice(1, 2);

            if (slotChoice == 1)
            {
                chosenPrimary = selected;
                ConsoleHelper::print("[+] " + selected->GetName() + " equipped as Primary!", ConsoleHelper::Green);
            }
            else
            {
                chosenSecondary = selected;
                ConsoleHelper::print("[+] " + selected->GetName() + " equipped as Secondary!", ConsoleHelper::Green);
            }
        }
    }

    if (chosenPrimary && chosenSecondary)
    {
        player->EquipWeapons(chosenPrimary, chosenSecondary);
    }

    for (Weapon* w : availableWeapons) {
        if (w != chosenPrimary && w != chosenSecondary) {
            delete w;
        }
    }
    availableWeapons.clear();
}

// Difficulty Selection Menu
GameDifficulty Game::SelectDifficulty()
{
    return GameUI::SelectDifficulty();
}