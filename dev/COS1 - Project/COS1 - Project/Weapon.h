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

    // --- BASE COMBAT METRICS ---
    int baseDamage;
    int postureDamage;

    // --- SCALING RATIOS ---
    float strScaling;
    float agiScaling;
    float intScaling;
    float focScaling;

    // --- RESOURCE COSTS ---
    int attackStaminaCost;
    int attackManaCost;
    int blockStaminaCost;
    int dodgeStaminaCost;

    // --- STATUS BUILDUPS ---
    int bleedBuildUp;
    int burnBuildUp;
    int frostbiteBuildUp;

    // --- COOLDOWN SYSTEM ---
    int shortCooldownRemaining;
    int longCooldownRemaining;

public:
    // --- CONSTRUCTORS ---
    Weapon(std::string name, WeaponType type, int baseDmg, int postureDmg,
        float strScale, float agiScale, float intScale, float focScale,
        int atkSP, int atkMP, int blockSP, int dodgeSP, int bleedVal, int burnVal, int frostbiteVal = 0);

    // --- DAMAGE CALCULATION & DISPLAY ---
    int CalculateDamage(int str, int agi, int intel, int foc) const;
    void DisplayWeaponInfo() const;

    // --- COOLDOWN & SKILL MANAGEMENT ---
    int GetShortCooldownRemaining() const;
    int GetLongCooldownRemaining() const;
    bool CanUseShortSkill() const;
    bool CanUseLongSkill() const;
    void TriggerShortSkill(int cooldownTurns);
    void TriggerLongSkill(int cooldownTurns);
    void UpdateCooldowns();

    // --- GETTERS ---
    std::string GetName() const { return name; }
    WeaponType GetType() const { return type; }
    int GetBaseDamage() const { return baseDamage; }
    int GetPostureDamage() const { return postureDamage; }

    int GetAttackStaminaCost() const { return attackStaminaCost; }
    int GetAttackManaCost() const { return attackManaCost; }
    int GetBlockStaminaCost() const { return blockStaminaCost; }
    int GetDodgeStaminaCost() const { return dodgeStaminaCost; }

    int GetBleedBuildUp() const { return bleedBuildUp; }
    int GetBurnBuildUp() const { return burnBuildUp; }
    int GetFrostbiteBuildUp() const { return frostbiteBuildUp; }
};
//Organized and Refactored