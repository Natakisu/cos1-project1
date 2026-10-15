#include <iostream>
#include "Weapon.h"

Weapon::Weapon(std::string name, WeaponType type, int baseDmg, int postureDmg,
    float strScale, float agiScale, float intScale, float focScale,
    int atkSP, int atkMP, int blockSP, int dodgeSP)
    : name(name), type(type), baseDamage(baseDmg), postureDamage(postureDmg),
    strScaling(strScale), agiScaling(agiScale), intScaling(intScale), focScaling(focScale),
    attackStaminaCost(atkSP), attackManaCost(atkMP),
    blockStaminaCost(blockSP), dodgeStaminaCost(dodgeSP) {
}

int Weapon::CalculateDamage(int str, int agi, int intel, int foc) const
{
    float bonusDamage = (str * strScaling) +
        (agi * agiScaling) +
        (intel * intScaling) +
        (foc * focScaling);

    return baseDamage + static_cast<int>(bonusDamage);
}

void Weapon::DisplayWeaponInfo() const {
    std::cout << "\033[36m--- " << name << " ---\033[0m\n";
    std::cout << "Base Damage: " << baseDamage << " | Posture Damage: " << postureDamage << "\n";
    std::cout << "Stamina Cost: " << attackStaminaCost << " | Mana Cost: " << attackManaCost << "\n";
    std::cout << "Scaling Ratios -> STR: " << (strScaling * 100) << "% | AGI: " << (agiScaling * 100)
        << "% | INT: " << (intScaling * 100) << "% | FOC: " << (focScaling * 100) << "%\n";
}