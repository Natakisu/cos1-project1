#include "WeaponManager.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <cstdlib>

WeaponManager::WeaponManager()
{
    InitializeWeaponPool();
}

WeaponManager::~WeaponManager()
{
    // Clean up any weapons that weren't picked (or clean all if unused)
    for (Weapon* w : availableWeapons)
    {
        delete w;
        w = nullptr;
    }
    availableWeapons.clear();
}

void WeaponManager::InitializeWeaponPool()
{
    availableWeapons.push_back(new Weapon("Warhammer", WeaponType::PureSTR, 25, 18, 1.0f, 0.0f, 0.0f, 0.0f, 25, 0, 20, 25, 0, 0));
    availableWeapons.push_back(new Weapon("Sword and Shield", WeaponType::PureSTR, 15, 10, 0.8f, 0.2f, 0.0f, 0.0f, 12, 5, 15, 18, 0, 0));

    availableWeapons.push_back(new Weapon("Daggers", WeaponType::PureAGI, 10, 6, 0.2f, 0.8f, 0.0f, 0.0f, 8, 0, 8, 10, 35, 0));
    availableWeapons.push_back(new Weapon("Bow", WeaponType::PureAGI, 14, 8, 0.1f, 0.9f, 0.0f, 0.0f, 10, 0, 10, 12, 0, 0));

    availableWeapons.push_back(new Weapon("Fire Staff", WeaponType::PureINT, 20, 5, 0.0f, 0.0f, 1.0f, 0.0f, 10, 15, 5, 15, 0, 40));
    availableWeapons.push_back(new Weapon("Ice Staff", WeaponType::PureINT, 16, 6, 0.0f, 0.0f, 0.9f, 0.1f, 8, 16, 6, 12, 0, 0, 35));

    availableWeapons.push_back(new Weapon("Life Staff", WeaponType::PureFOC, 12, 4, 0.0f, 0.0f, 0.0f, 1.0f, 6, 12, 10, 15, 0, 0));

    availableWeapons.push_back(new Weapon("Greatsword", WeaponType::Hybrid, 22, 14, 0.5f, 0.5f, 0.0f, 0.0f, 20, 0, 15, 20, 0, 0));
    availableWeapons.push_back(new Weapon("Rapier", WeaponType::Hybrid, 13, 7, 0.2f, 0.4f, 0.4f, 0.0f, 9, 8, 7, 12, 0, 0));
    availableWeapons.push_back(new Weapon("Flail and Shield", WeaponType::Hybrid, 17, 12, 0.4f, 0.0f, 0.0f, 0.6f, 15, 8, 14, 18, 0, 0));
}

void WeaponManager::SelectPlayerLoadout(Weapon*& outPrimary, Weapon*& outSecondary)
{
    bool weaponsConfirmed = false;

    Weapon* chosenPrimary = nullptr;
    Weapon* chosenSecondary = nullptr;

    while (!weaponsConfirmed)
    {
        system("cls");
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
                if (selected == chosenSecondary)
                {
                    ConsoleHelper::print("[!] You cannot equip the same weapon in both slots!", ConsoleHelper::Red);
                }
                else
                {
                    chosenPrimary = selected;
                    ConsoleHelper::print("[+] " + selected->GetName() + " equipped as Primary!", ConsoleHelper::Green);
                }
            }
            else
            {
                if (selected == chosenPrimary)
                {
                    ConsoleHelper::print("[!] You cannot equip the same weapon in both slots!", ConsoleHelper::Red);
                }
                else
                {
                    chosenSecondary = selected;
                    ConsoleHelper::print("[+] " + selected->GetName() + " equipped as Secondary!", ConsoleHelper::Green);
                }
            }
        }
    }

    // Safeguard against duplicate pointers
    if (chosenPrimary == chosenSecondary && chosenPrimary != nullptr)
    {
        chosenSecondary = nullptr;
    }

    // Pass the finalized choices back out to the caller
    outPrimary = chosenPrimary;
    outSecondary = chosenSecondary;

    // Clear vector pointers from local list tracking so they don't get deleted when WeaponManager goes out of scope 
    // (since they are now owned by the Player object)
    availableWeapons.clear();
}
