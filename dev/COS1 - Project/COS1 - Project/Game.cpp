#include "Game.h"
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

void Game::Initialize()
{
    CharacterCreation();
    //Add weapon menu to UI to let character select weapon
    WeaponSelectionMenu();
    currentBoss = new Enemy("Relic Guardian", 10000000, 500);
}

void Game::CharacterCreation()
{
    std::string playerName;
    std::cout << "========================================\n";
    std::cout << "          CHARACTER CREATION            \n";
    std::cout << "========================================\n";
    std::cout << "Enter your character's name: ";
    std::cin >> playerName;
    player = new Player(playerName);

    int totalPoints = 30; // Total points available to spend
    int con = 10, str = 10, agi = 10, intel = 10, foc = 10; // Base starting stats

    // Breif Description of what Stats do
    std::cout << "\n--- Attribute Descriptions ---\n";
    std::cout << " - Constitution (CON): Increases your Max HP.\n";
    std::cout << " - Strength     (STR): Increases physical weapon damage.\n";
    std::cout << " - Agility      (AGI): Increases Stamina (SP) and dodging/speed.\n";
    std::cout << " - Intellect    (INT): Increases Mana (MP) and magical effectiveness.\n";
    std::cout << " - Focus        (FOC): Increases your healing potency and recovery\n";

    std::cout << "\n--- Stat Allocation (30 Points Available) ---\n";
    std::cout << "(Base stats start at 10. Enter how many points to *add* to each)\n";

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

    std::cout << "\n========================================\n";
    std::cout << "       ATTRIBUTES CONFIGURED!           \n";
    std::cout << "========================================\n";
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

int Game::GetValidatedPlayerChoice()
{
    int choice = 0;
    std::string inputLine;
    bool isValid = false;

    while (!isValid)
    {
        std::cout << "Choice: ";
        // Grab the entire line of input
        std::getline(std::cin, inputLine);

        try
        {
            // Attempt to convert string to integer
            choice = std::stoi(inputLine);

            // Check range for the 6 menu items
            if (choice >= 1 && choice <= 6)
            {
                isValid = true;
            }
            else
            {
                std::cout << "[!] Invalid choice. Please enter a number between 1 and 6.\n";
            }
        }
        catch (const std::invalid_argument&)
        {
            // Catch if the user types letters or symbols instead of a number
            std::cout << "[!] Invalid input. Please enter a valid number.\n";
        }
        catch (const std::out_of_range&)
        {
            // Catch if the number is way too large/small 
            std::cout << "[!] Number out of range. Please enter a valid menu number.\n";
        }
    }

    return choice;
}

void Game::HandlePlayerAction(int choice)
{
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
        std::cout << "Swapped weapons!\n";
        break;
    case 4:
        player->Block();
        break;
    case 5:
        player->Dodge();
        break;
    case 6:
        player->InspectWeapons();
        break;
    }
}

void Game::HandleCombatOutcome() const
{
    if (!player->IsAlive())
    {
        std::cout << "\nYou were defeated!\n";
    }
    else if (!currentBoss->IsAlive())
    {
        std::cout << "\nYou defeated the Relic Guardian!\n";
    }
}

void Game::RunCombatLoop()
{
    while (isRunning && player->IsAlive() && currentBoss->IsAlive())
    {
        currentBoss->GenerateIntent();
        RenderUI();
        DisplayMenu();

        int choice = GetValidatedPlayerChoice();
        HandlePlayerAction(choice);

        // If player inspected or swapped weapons, skip enemy turn / free action flow
        if (choice == 3 || choice == 6) 
        {
            continue;
        }

        // Boss resolves action after player turn
        if (currentBoss->IsAlive()) 
        {
            currentBoss->ExecuteIntent(*player);
            player->RegainResourcesPerTurn();
            currentBoss->ResetTurnState();
        }
    }

    HandleCombatOutcome();
    isRunning = false;
}

void Game::InitializeWeaponPool()
{
    // [Pure STR Weapons]
    // Warhammer:
    availableWeapons.push_back(new Weapon("Warhammer", WeaponType::PureSTR, 25, 18, 1.0f, 0.0f, 0.0f, 0.0f, 25, 0, 20, 25));
    // Sword and Shield: Balanced offensive/defensive with high block stability.
    availableWeapons.push_back(new Weapon("Sword and Shield", WeaponType::PureSTR, 15, 10, 0.8f, 0.2f, 0.0f, 0.0f, 12, 5, 15, 18));

    // [Pure AGI Weapons]
    // Daggers:
    availableWeapons.push_back(new Weapon("Daggers", WeaponType::PureAGI, 10, 6, 0.2f, 0.8f, 0.0f, 0.0f, 8, 0, 8, 10));
    // Bow: Ranged physical damage, quick shots or aimed high damage.
    availableWeapons.push_back(new Weapon("Bow", WeaponType::PureAGI, 14, 8, 0.1f, 0.9f, 0.0f, 0.0f, 10, 0, 10, 12));

    // [Pure INT Weapons]
    // Fire Staff:
    availableWeapons.push_back(new Weapon("Fire Staff", WeaponType::PureINT, 20, 5, 0.0f, 0.0f, 1.0f, 0.0f, 10, 15, 5, 15));
    // Ice Staff: Control and mitigation; reduces enemy stamina regeneration.
    availableWeapons.push_back(new Weapon("Ice Staff", WeaponType::PureINT, 16, 6, 0.0f, 0.0f, 0.9f, 0.1f, 8, 16, 6, 12));

    // [Pure FOC Weapons]
    // Life Staff:
    availableWeapons.push_back(new Weapon("Life Staff", WeaponType::PureFOC, 12, 4, 0.0f, 0.0f, 0.0f, 1.0f, 6, 12, 10, 15));

    // [Hybrid Weapons]
    // Greatsword (STR / AGI):
    availableWeapons.push_back(new Weapon("Greatsword", WeaponType::Hybrid, 22, 14, 0.5f, 0.5f, 0.0f, 0.0f, 20, 0, 15, 20));
    // Rapier (AGI / INT):
    availableWeapons.push_back(new Weapon("Rapier", WeaponType::Hybrid, 13, 7, 0.2f, 0.4f, 0.4f, 0.0f, 9, 8, 7, 12));
    // Flail and Shield (STR / FOC):
    availableWeapons.push_back(new Weapon("Flail and Shield", WeaponType::Hybrid, 17, 12, 0.4f, 0.0f, 0.0f, 0.6f, 15, 8, 14, 18));
}

// Weapon Menu
void Game::WeaponSelectionMenu()
{
    bool weaponsConfirmed = false;

    // Initialize the master weapon pool once
    InitializeWeaponPool();

    // Track chosen weapon pointers temporarily
    Weapon* chosenPrimary = nullptr;
    Weapon* chosenSecondary = nullptr;

    while (!weaponsConfirmed)
    {
        // Display current loadout status so the player knows what they've locked in so far
        std::cout << "\n========================================\n";
        std::cout << "          WEAPON SELECTION MENU         \n";
        std::cout << "========================================\n";
        std::cout << "Current Primary:   " << (chosenPrimary ? chosenPrimary->GetName() : "[None Selected]") << "\n";
        std::cout << "Current Secondary: " << (chosenSecondary ? chosenSecondary->GetName() : "[None Selected]") << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "1. Pure Strength (STR) Weapons\n";
        std::cout << "2. Pure Agility (AGI) Weapons\n";
        std::cout << "3. Pure Intellect (INT) Weapons\n";
        std::cout << "4. Pure Focus (FOC) Weapons\n";
        std::cout << "5. Hybrid Weapons\n";
        std::cout << "6. View All Weapons\n";
        if (chosenPrimary != nullptr && chosenSecondary != nullptr) {
            std::cout << "7. Finish & Confirm Loadout\n";
        }
        std::cout << "Select a category (1-" << (chosenPrimary && chosenSecondary ? "7" : "6") << "): ";

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

        std::cout << "\n========================================\n";
        std::cout << "         AVAILABLE WEAPONS IN GROUP     \n";
        std::cout << "========================================\n";

        for (size_t i = 0; i < filteredWeapons.size(); ++i)
        {
            std::cout << i + 1 << ". ";
            filteredWeapons[i]->DisplayWeaponInfo();

            std::string name = filteredWeapons[i]->GetName();
            std::cout << "   -> Description: ";
            if (name == "Warhammer")
                std::cout << "Slower attack speed, high physical damage, massive posture damage.\n";
            else if (name == "Sword and Shield")
                std::cout << "Balanced offensive/defensive with high block stability.\n";
            else if (name == "Daggers")
                std::cout << "Fast attack speed, multi-hits, rapid Bleed buildup.\n";
            else if (name == "Bow")
                std::cout << "Ranged physical damage; quick shots or aimed high damage.\n";
            else if (name == "Fire Staff")
                std::cout << "High magic damage with Burn status buildup (damage over time).\n";
            else if (name == "Ice Staff")
                std::cout << "Control & mitigation; reduces enemy stamina regeneration.\n";
            else if (name == "Life Staff")
                std::cout << "Essential sustain; self-healing and cooldown reduction.\n";
            else if (name == "Greatsword")
                std::cout << "Hybrid: Heavy attacks scale with STR; light multi-hits scale with AGI.\n";
            else if (name == "Rapier")
                std::cout << "Hybrid: Finesse weapon with cross-resource detonation (Bleed/Burn).\n";
            else if (name == "Flail and Shield")
                std::cout << "Hybrid: Paladin drain-tanking with a small self-heal on attack/block.\n";
            else
                std::cout << "Standard combat weapon.\n";

            std::cout << "----------------------------------------\n";
        }

        std::cout << "Enter 0 to go back to category menu without picking.\n";
        std::cout << "Select a weapon to assign (1-" << filteredWeapons.size() << ", or 0 to go back): ";

        std::string wInput;
        std::getline(std::cin, wInput);
        int weaponChoice = 0;
        try { weaponChoice = std::stoi(wInput); }
        catch (...) { weaponChoice = 0; }

        if (weaponChoice > 0 && weaponChoice <= (int)filteredWeapons.size())
        {
            Weapon* selected = filteredWeapons[weaponChoice - 1];

            std::cout << "\nAssign " << selected->GetName() << " to:\n";
                std::cout << "1. Primary Slot\n";
            std::cout << "2. Secondary Slot\n";
            std::cout << "Choice: ";

            std::string slotInput;
            std::getline(std::cin, slotInput);
            int slotChoice = 0;
            try { slotChoice = std::stoi(slotInput); }
            catch (...) { slotChoice = 1; }

            if (slotChoice == 1)
            {
                chosenPrimary = selected;
                std::cout << "[+] " << selected->GetName() << " equipped as Primary!\n";
            }
            else
            {
                chosenSecondary = selected;
                std::cout << "[+] " << selected->GetName() << " equipped as Secondary!\n";
            }
        }
    }

    // Equip final selections to player
    if (chosenPrimary && chosenSecondary)
    {
        player->EquipWeapons(new Weapon(*chosenPrimary), new Weapon(*chosenSecondary));
    }

    // Clean up master pool memory
    for (Weapon* w : availableWeapons) {
        delete w;
    }
    availableWeapons.clear();
}