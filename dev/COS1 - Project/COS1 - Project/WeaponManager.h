#pragma once
#include <vector>
#include "Weapon.h"

class WeaponManager
{
private:
    std::vector<Weapon*> availableWeapons;

    void InitializeWeaponPool();

public:
    WeaponManager();
    ~WeaponManager();

    // Runs the interactive selection loop and outputs chosen primary and secondary weapons
    void SelectPlayerLoadout(Weapon*& outPrimary, Weapon*& outSecondary);
};