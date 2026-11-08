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

    // Status Buildups (Bleed, Burn, Frostbite)
    int bleedBuildUp;
    int burnBuildUp;
    int frostbiteBuildUp;

    // Cooldown System
    int shortCooldownRemaining;
    int longCooldownRemaining;

public:
    Weapon(std::string name, WeaponType type, int baseDmg, int postureDmg,
        float strScale, float agiScale, float intScale, float focScale,
        int atkSP, int atkMP, int blockSP, int dodgeSP, int bleedVal, int burnVal, int frostbiteVal = 0); // Added default param for backward compatibility

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

    // Status Buildup Getters
    int GetBleedBuildUp() const { return bleedBuildUp; }
    int GetBurnBuildUp() const { return burnBuildUp; }
    int GetFrostbiteBuildUp() const { return frostbiteBuildUp; }

    // Cooldown Tracker
    void UpdateCooldowns() {
        if (shortCooldownRemaining > 0) shortCooldownRemaining--;
        if (longCooldownRemaining > 0) longCooldownRemaining--;
    }

    bool CanUseShortSkill() const { return shortCooldownRemaining == 0; }
    bool CanUseLongSkill() const { return longCooldownRemaining == 0; }

    void TriggerShortSkill(int duration) { shortCooldownRemaining = duration; }
    void TriggerLongSkill(int duration) { longCooldownRemaining = duration; }
};
