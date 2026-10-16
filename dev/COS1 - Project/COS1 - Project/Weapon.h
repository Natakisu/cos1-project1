#pragma once
#include <string>

enum class WeaponType
{
    PureSTR,
    PureAGI,
    PureINT,
    PureFOC,
    Hybrid
};

class Weapon
{
private:
    std::string name;
    WeaponType type;

    // Base Combat Metrics
    int baseDamage;
    int postureDamage;

    // Scaling Ratios
    float strScaling;
    float agiScaling;
    float intScaling;
    float focScaling;

    // Resource Costs
    int attackStaminaCost;
    int attackManaCost;
    int blockStaminaCost;
    int dodgeStaminaCost;

    // Bleed and Burn
    int bleedBuildUp;
    int burnBuildUp;

public:
    Weapon(std::string name, WeaponType type, int baseDmg, int postureDmg,
        float strScale, float agiScale, float intScale, float focScale,
        int atkSP, int atkMP, int blockSP, int dodgeSP, int bleedVal, int burnVal);

    // Getters
    std::string GetName() const { return name; }
    int GetBaseDamage() const { return baseDamage; }
    int GetPostureDamage() const { return postureDamage; }
    int GetAttackStaminaCost() const { return attackStaminaCost; }
    int GetAttackManaCost() const { return attackManaCost; }
    int GetBlockStaminaCost() const { return blockStaminaCost; }
    int GetDodgeStaminaCost() const { return dodgeStaminaCost; }
    WeaponType GetType() const { return type; }

    // Scaled Damage Calculation
    int CalculateDamage(int str, int agi, int intel, int foc) const;

    void DisplayWeaponInfo() const;

    // Bleed and Burn
    int GetBleedBuildUp() const { return bleedBuildUp; }
    int GetBurnBuildUp() const { return burnBuildUp; }
};