#pragma once
#include <vector>
#include "Weapon.h"

class WeaponManager
{
private:
    std::vector<Weapon*> availableWeapons;

    // --- INITIALIZATION ---
    void InitializeWeaponPool();

public:
    // --- CONSTRUCTORS & DESTRUCTOR ---
    WeaponManager();
    ~WeaponManager();

    // --- LOADOUT SELECTION INTERFACE ---

    // Runs the interactive selection loop and outputs chosen primary and secondary weapons
    void SelectPlayerLoadout(Weapon*& outPrimary, Weapon*& outSecondary);
};
//Organized and Refactored