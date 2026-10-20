#include "Game.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <string>

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
        system("cls"); // Clears the screen at the start of every loop iteration

        ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("               [ RELIC SWITCHER ]                 ", ConsoleHelper::Cyan);
        ConsoleHelper::print("          A C++ Console RPG Experience            ", ConsoleHelper::White);
        ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print(" 1. Start New Game                                ", ConsoleHelper::White);
        ConsoleHelper::print(" 2. View Instructions                             ", ConsoleHelper::White);
        ConsoleHelper::print(" 3. Exit Game                                     ", ConsoleHelper::White);
        ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Choice (1-3): ", ConsoleHelper::Cyan, false);

        std::string input;
        std::getline(std::cin, input);
        int choice = 0;

        try {
            choice = std::stoi(input);
        }
        catch (...) {
            choice = 0;
        }

        if (choice == 1)
        {
            inWelcomeMenu = false; // Proceeds forward into character creation & game
        }
        else if (choice == 2)
        {
            system("cls"); // Clear the menu before showing instructions

            ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
            ConsoleHelper::print("                  GAME INSTRUCTIONS                ", ConsoleHelper::Cyan);
            ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
            ConsoleHelper::print(" - Relic Switcher is a Turn-Based RPG with elements", ConsoleHelper::White);
            ConsoleHelper::print("    from New World Aeternum and Dark Souls         ", ConsoleHelper::White);
            ConsoleHelper::print(" - Allocate attributes wisely during creation.     ", ConsoleHelper::White);
            ConsoleHelper::print(" - Choose a Primary and Secondary weapon loadout.  ", ConsoleHelper::White);
            ConsoleHelper::print(" - Choose a Difficulty you would like to play.     ", ConsoleHelper::White);
            ConsoleHelper::print(" - Fight the Relic Guardian using Attacks, Blocks, ", ConsoleHelper::White);
            ConsoleHelper::print("    and Dodges while managing your HP, SP, and MP. ", ConsoleHelper::White);
            ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
            ConsoleHelper::print("Press Enter to return to the main menu...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
        else if (choice == 3)
        {
            ConsoleHelper::print("\nExiting game. Thanks for playing!", ConsoleHelper::Green);
            exit(0); // Clean exit
        }
        else
        {
            ConsoleHelper::print("[!] Invalid choice. Please enter 1, 2, or 3.", ConsoleHelper::Red);
            ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }
}

// Main Menu
void Game::Initialize()
{
    isRunning = true; 

    DisplayWelcomeMenu();
    system("cls");
    CharacterCreation();
    WeaponSelectionMenu();

    currentDifficulty = SelectDifficulty();

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
    player = new Player(playerName);

    int totalPoints = 30; // Total points available to spend
    int con = 10, str = 10, agi = 10, intel = 10, foc = 10; // Base starting stats

    // Breif Description of what Stats do
    ConsoleHelper::print("\n--- Attribute Descriptions ---", ConsoleHelper::Cyan);
    ConsoleHelper::print(" - Constitution (CON): Increases your Max HP.", ConsoleHelper::White);
    ConsoleHelper::print(" - Strength     (STR): Increases physical weapon damage.", ConsoleHelper::White);
    ConsoleHelper::print(" - Agility      (AGI): Increases Stamina (SP) and dodging/speed.", ConsoleHelper::White);
    ConsoleHelper::print(" - Intellect    (INT): Increases Mana (MP) and magical effectiveness.", ConsoleHelper::White);
    ConsoleHelper::print(" - Focus        (FOC): Increases your healing potency and recovery", ConsoleHelper::White);

    ConsoleHelper::print("\n--- Stat Allocation (30 Points Available) ---", ConsoleHelper::Cyan);
    ConsoleHelper::print("(Base stats start at 10. Enter how many points to [ADD] to each)", ConsoleHelper::White);

    int p = 0;

    // Constitution
    std::cout << "\n[1/5] Constitution (CON) [Pool Left: " << totalPoints << "]: ";
    std::cin >> p;
    if (p > totalPoints) p = totalPoints;
    con += p;
    totalPoints -= p;

    // Strength
    if (totalPoints > 0)
    {
        std::cout << "[2/5] Strength (STR) [Pool Left: " << totalPoints << "]: ";
        std::cin >> p;
        if (p > totalPoints) p = totalPoints;
        str += p;
        totalPoints -= p;
    }

    // Agility
    if (totalPoints > 0)
    {
        std::cout << "[3/5] Agility (AGI) [Pool Left: " << totalPoints << "]: ";
        std::cin >> p;
        if (p > totalPoints) p = totalPoints;
        agi += p;
        totalPoints -= p;
    }

    // Intellect
    if (totalPoints > 0)
    {
        std::cout << "[4/5] Intellect (INT) [Pool Left: " << totalPoints << "]: ";
        std::cin >> p;
        if (p > totalPoints) p = totalPoints;
        intel += p;
        totalPoints -= p;
    }

    // Focus (dumps any remaining pool points automatically)
    foc += totalPoints;
    std::cout << "[5/5] Focus (FOC): Remaining " << totalPoints << " points automatically allocated.\n";

    // Apply the configured values
    player->SetAttributes(con, str, agi, intel, foc);

    system("cls"); // Clear allocation text before showing final summary if desired

    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("     [ ATTRIBUTES CONFIGURED! ]         ", ConsoleHelper::Cyan);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);
    player->DisplayStats();
}

// HP, SP, MP Bars
void Game::RenderUI() const
{
    if (!player || !currentBoss) return;

    // Lambda helper function using ConsoleHelper colors for the progress bar
    auto drawBar = [](int current, int max, int totalBlocks = 10) {
        if (max <= 0) max = 1;
        float ratio = static_cast<float>(current) / max;
        if (ratio < 0.0f) ratio = 0.0f;
        if (ratio > 1.0f) ratio = 1.0f;
        int filledCount = static_cast<int>(ratio * totalBlocks);
        std::cout << "[";
        for (int i = 0; i < totalBlocks; ++i) {
            if (i < filledCount) {
                ConsoleHelper::print("#", ConsoleHelper::Green, false); // Green filled block
            }
            else {
                ConsoleHelper::print("-", ConsoleHelper::Red, false);   // Red empty block slot
            }
        }
        std::cout << "] " << current << "/" << max;
        };
    ConsoleHelper::print("\n==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print(" PLAYER: " + player->GetName(), ConsoleHelper::White);
    std::cout << " HP: "; drawBar(player->GetCurrentHP(), player->GetMaxHP()); std::cout << "\n";
    std::cout << " SP: "; drawBar(player->GetCurrentSP(), player->GetMaxSP()); std::cout << "\n";
    std::cout << " MP: "; drawBar(player->GetCurrentMP(), player->GetMaxMP()); std::cout << "\n";
    ConsoleHelper::print("--------------------------------------------------", ConsoleHelper::Cyan);
    ConsoleHelper::print(" BOSS:   " + currentBoss->GetName(), ConsoleHelper::White);

    // Boss HP Bar
    std::cout << " HP:      "; drawBar(currentBoss->GetCurrentHP(), currentBoss->GetMaxHP()); std::cout << "\n";

    // Boss Posture Bar
    std::cout << " Posture: "; drawBar(currentBoss->GetCurrentPosture(), currentBoss->GetMaxPosture()); std::cout << "\n";

    // Status Effect Buildup Bars
    std::cout << " Bleed:   "; drawBar(currentBoss->GetBleedMeter(), 100); std::cout << "\n";
    std::cout << " Burn:    "; drawBar(currentBoss->GetBurnMeter(), 100); std::cout << "\n";

    ConsoleHelper::print(" BOSS INTENT: ", ConsoleHelper::White, false);
    ConsoleHelper::print(currentBoss->GetIntentDescription(), ConsoleHelper::Yellow);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
}

// Combat Action Menu
void Game::DisplayMenu() const
{
    ConsoleHelper::print("1. Light Attack", ConsoleHelper::White);
    ConsoleHelper::print("2. Heavy Attack", ConsoleHelper::White);
    ConsoleHelper::print("3. Swap Weapon", ConsoleHelper::White);
    ConsoleHelper::print("4. Block", ConsoleHelper::White);
    ConsoleHelper::print("5. Dodge", ConsoleHelper::White);
    ConsoleHelper::print("6. Inspect Weapons", ConsoleHelper::White);
}

// Try-Catch
int Game::GetValidatedPlayerChoice()
{
    int choice = 0;
    std::string inputLine;
    bool isValid = false;

    while (!isValid)
    {
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }

        ConsoleHelper::print("Choice: ", ConsoleHelper::Cyan, false);

        if (!std::getline(std::cin, inputLine))
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        if (inputLine.empty())
        {
            continue;
        }

        try
        {
            choice = std::stoi(inputLine);
            if (choice >= 1 && choice <= 6)
            {
                isValid = true;
            }
            else
            {
                ConsoleHelper::print("[!] Invalid choice. Please enter a number between 1 and 6.", ConsoleHelper::Red);
            }
        }
        catch (...)
        {
            ConsoleHelper::print("[!] Invalid input. Please enter a valid number.", ConsoleHelper::Red);
        }
    }

    return choice;
}

// Weapon Swap and Healing
void Game::HandlePlayerAction(int choice)
{
    Weapon* activeWeapon = player->GetActiveWeapon(); // Grab active weapon pointer

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

        // Apply status buildup on light attack
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

        // ---> Apply status buildup on heavy attack
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
        // 1. Check if player died
        if (!player->IsAlive())
        {
            break;
        }

        // 2. Check if boss died
        if (!currentBoss->IsAlive())
        {
            system("cls");
            HandleCombatOutcome(); // Shows the victory/outcome header

            // Award XP and explicitly print the gained amount to the console
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

                player->GainXP(earnedXP); // This will handle your level-up messages internally

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
        RenderUI();
        DisplayMenu();

        int choice = GetValidatedPlayerChoice();
        HandlePlayerAction(choice);

        // Weapon inspect or swap handled without full combat progression
        if (choice == 6 || choice == 3)
        {
            if (std::cin.peek() == '\n') std::cin.ignore();
            ConsoleHelper::print("\nPress Enter to return to combat...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }

        // --- COMBAT TURN RESOLUTION ---
        // Resolve status effects on boss
        currentBoss->ResolveStatusEffects();
        if (!currentBoss->IsAlive()) continue; // Re-check at top of loop for clean victory handling

        // Execute boss action
        currentBoss->ExecuteIntent(*player);
        if (!player->IsAlive()) break;

        // Single consolidated pause per complete turn round
        if (std::cin.peek() == '\n') std::cin.ignore();
        ConsoleHelper::print("\n[Turn Complete] Press Enter to continue...", ConsoleHelper::Cyan, false);
        std::string pauseInput;
        std::getline(std::cin, pauseInput);

        player->RegainResourcesPerTurn();
        currentBoss->ResetTurnState();
    }

    // If player lost
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
    // Parameters: (Name, Type, BaseDmg, PostureDmg, StrScale, AgiScale, IntScale, FocScale, AtkSP, AtkMP, BlockSP, DodgeSP, BleedVal, BurnVal)

    // [Pure STR Weapons]
    // Warhammer:
    availableWeapons.push_back(new Weapon("Warhammer", WeaponType::PureSTR, 25, 18, 1.0f, 0.0f, 0.0f, 0.0f, 25, 0, 20, 25, 0, 0));
    // Sword and Shield: Balanced offensive/defensive with high block stability.
    availableWeapons.push_back(new Weapon("Sword and Shield", WeaponType::PureSTR, 15, 10, 0.8f, 0.2f, 0.0f, 0.0f, 12, 5, 15, 18, 0, 0));

    // [Pure AGI Weapons]
    // Daggers: Exclusive Bleed Applier
    availableWeapons.push_back(new Weapon("Daggers", WeaponType::PureAGI, 10, 6, 0.2f, 0.8f, 0.0f, 0.0f, 8, 0, 8, 10, 35, 0));
    // Bow: Ranged physical damage, quick shots or aimed high damage.
    availableWeapons.push_back(new Weapon("Bow", WeaponType::PureAGI, 14, 8, 0.1f, 0.9f, 0.0f, 0.0f, 10, 0, 10, 12, 0, 0));

    // [Pure INT Weapons]
    // Fire Staff: Exclusive Burn Applier
    availableWeapons.push_back(new Weapon("Fire Staff", WeaponType::PureINT, 20, 5, 0.0f, 0.0f, 1.0f, 0.0f, 10, 15, 5, 15, 0, 40));
    // Ice Staff: Control and mitigation; reduces enemy stamina regeneration.
    availableWeapons.push_back(new Weapon("Ice Staff", WeaponType::PureINT, 16, 6, 0.0f, 0.0f, 0.9f, 0.1f, 8, 16, 6, 12, 0, 0));

    // [Pure FOC Weapons]
    // Life Staff:
    availableWeapons.push_back(new Weapon("Life Staff", WeaponType::PureFOC, 12, 4, 0.0f, 0.0f, 0.0f, 1.0f, 6, 12, 10, 15, 0, 0));

    // [Hybrid Weapons]
    // Greatsword (STR / AGI):
    availableWeapons.push_back(new Weapon("Greatsword", WeaponType::Hybrid, 22, 14, 0.5f, 0.5f, 0.0f, 0.0f, 20, 0, 15, 20, 0, 0));
    // Rapier (AGI / INT):
    availableWeapons.push_back(new Weapon("Rapier", WeaponType::Hybrid, 13, 7, 0.2f, 0.4f, 0.4f, 0.0f, 9, 8, 7, 12, 0, 0));
    // Flail and Shield (STR / FOC):
    availableWeapons.push_back(new Weapon("Flail and Shield", WeaponType::Hybrid, 17, 12, 0.4f, 0.0f, 0.0f, 0.6f, 15, 8, 14, 18, 0, 0));
}

// Weapon Menu
void Game::WeaponSelectionMenu()
{
    bool weaponsConfirmed = false;

    // Initialize the master weapon pool once
    InitializeWeaponPool();

    // Track chosen weapon pointers temporarily across category
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
        std::cout << "Choice (1-" << (chosenPrimary && chosenSecondary ? "7" : "6") << "): ";
        ConsoleHelper::print("", ConsoleHelper::Cyan, false);

        if (std::cin.peek() == '\n') {
            std::cin.ignore();
        }

        std::string catInput;
        std::getline(std::cin, catInput);
        int categoryChoice = 0;

        try {
            categoryChoice = std::stoi(catInput);
        }
        catch (...) {
            categoryChoice = 6;
        }

        // If they chose option 7 to finish
        if (categoryChoice == 7 && chosenPrimary != nullptr && chosenSecondary != nullptr)
        {
            weaponsConfirmed = true;
            break;
        }

        // Filter weapons based on the chosen category
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
        std::cout << "Select a weapon to assign (1-" << filteredWeapons.size() << ", or 0 to go back): ";
        ConsoleHelper::print("", ConsoleHelper::Cyan, false);

        std::string wInput;
        std::getline(std::cin, wInput);
        int weaponChoice = 0;
        try { weaponChoice = std::stoi(wInput); }
        catch (...) { weaponChoice = 0; }

        if (weaponChoice > 0 && weaponChoice <= (int)filteredWeapons.size())
        {
            Weapon* selected = filteredWeapons[weaponChoice - 1];

            std::cout << "\nAssign " << selected->GetName() << " to:\n";
            ConsoleHelper::print("1. Primary Slot", ConsoleHelper::White);
            ConsoleHelper::print("2. Secondary Slot", ConsoleHelper::White);
            ConsoleHelper::print("Choice: ", ConsoleHelper::Cyan, false);

            std::string slotInput;
            std::getline(std::cin, slotInput);
            int slotChoice = 0;
            try { slotChoice = std::stoi(slotInput); }
            catch (...) { slotChoice = 1; }

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

    // Equip final selections to player
    if (chosenPrimary && chosenSecondary)
    {
        player->EquipWeapons(chosenPrimary, chosenSecondary);
    }

    // Clean up master pool memory (deleting unchosen weapons, leaving player-owned ones safe)
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
    bool difficultyChosen = false;
    GameDifficulty chosenDifficulty = GameDifficulty::Normal;

    while (!difficultyChosen)
    {
        system("cls");
        ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("                    [ SELECT GAME DIFFICULTY ]                    |", ConsoleHelper::Cyan);
        ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print(" 1. Easy       (Boss HP: 500     | Barely A Challenge  | XP:  150)|", ConsoleHelper::Green);
        ConsoleHelper::print(" 2. Normal     (Boss HP: 5000    | Standard Experience | XP:  300)|", ConsoleHelper::Cyan);
        ConsoleHelper::print(" 3. Hard       (Boss HP: 50000   | Harder Experience   | XP:  600)|", ConsoleHelper::White);
        ConsoleHelper::print(" 4. Insane     (Boss HP: 500000  | Soulslike Challenge | XP: 1200)|", ConsoleHelper::Yellow);
        ConsoleHelper::print(" 5. Impossible (Boss HP: 5000000 | Why? Why Do This?   | XP: 2400)|", ConsoleHelper::Red);
        ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Choice (1-5): ", ConsoleHelper::Cyan, false);

        std::string input;
        std::getline(std::cin, input);
        int choice = 0;

        try {
            choice = std::stoi(input);
        }
        catch (...) {
            choice = 0;
        }

        if (choice >= 1 && choice <= 5)
        {
            chosenDifficulty = static_cast<GameDifficulty>(choice - 1);
            difficultyChosen = true;
        }
        else
        {
            ConsoleHelper::print("[!] Invalid selection. Please choose a number between 1 and 5.", ConsoleHelper::Red);
            ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }

    return chosenDifficulty;
}