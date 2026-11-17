#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Weapon.h"
#include "Item.h"

class Enemy;
class WeaponSkillManager;

class Player
{
    friend class WeaponSkillManager;

private:
    std::string name;

    // Core Attributes
    int constitution; // CON
    int strength;     // STR
    int agility;      // AGI
    int intellect;    // INT
    int focus;        // FOC

    // Calculated Pools & Current Values
    int maxHP, currentHP;
    int maxSP, currentSP;
    int maxMP, currentMP;

    // Dual-Weapon Slots
    Weapon* primaryWeapon;
    Weapon* secondaryWeapon;
    bool isPrimaryActive;

    // Combat Stances
    bool isBlocking;
    bool isFullBlocking;
    bool isDodging;

    // XP & Progression System
    int level;
    int currentXP;
    int xpToNextLevel;
    int unspentAttributePoints;

    // Inventory & Currency
    std::vector<Item*> inventory;
    int relicShards;

public:
    // --- CONSTRUCTORS & DESTRUCTOR ---
    Player(std::string name);
    ~Player();

    // --- SETUP & ATTRIBUTE PROGRESSION ---
    void AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints);
    void SetAttributes(int con, int str, int agi, int intel, int foc);
    void AllocateAttribute(int choice, int amount);
    void RecalculatePools();
    void UpdateDerivedStats();
    void EquipWeapons(Weapon* primary, Weapon* secondary);
    void DisplayStats() const;
    void InspectWeapons() const;

    // --- COMBAT ACTIONS & RESOURCE MANAGEMENT ---
    bool SwapWeapon();
    bool ExecuteWeaponSkill(bool isLongSkill, Enemy& target);
    int PerformLightAttack(Enemy& target);
    int PerformHeavyAttack(Enemy& target);
    void Block();
    void FullBlock() { isFullBlocking = true; }
    void Dodge();
    void RegainResourcesPerTurn();
    void TakeDamage(int damage);

    void Heal(int amount) { currentHP = std::min(maxHP, currentHP + amount); }
    void RestoreMP(int amount) { currentMP = std::min(maxMP, currentMP + amount); }
    void ConsumeSP(int amount) { currentSP = std::max(0, currentSP - amount); }
    void ConsumeMP(int amount) { currentMP = std::max(0, currentMP - amount); }

    // --- INVENTORY & MAGIC BLESSINGS ---
    void AddItem(Item* item);
    void UseItem(int index);
    void CastMagicBlessing(Item* item, Enemy* target);
    const std::vector<Item*>& GetInventory() const;

    // --- XP & CURRENCY ---
    void GainXP(int amount);
    void AddUnspentPoints(int amount) { unspentAttributePoints += amount; }
    void AddRelicShards(int amount) { relicShards += amount; }
    void SpendRelicShards(int amount) { if (relicShards >= amount) relicShards -= amount; }

    // --- SAVE & LOAD ---
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void AutoSave() const { SaveToFile(name + "_save.txt"); }

    // --- GETTERS ---
    std::string GetName() const { return name; }
    bool IsAlive() const { return currentHP > 0; }
    Weapon* GetActiveWeapon() const { return isPrimaryActive ? primaryWeapon : secondaryWeapon; }

    int GetCurrentHP() const { return currentHP; }
    int GetMaxHP() const { return maxHP; }
    int GetCurrentSP() const { return currentSP; }
    int GetMaxSP() const { return maxSP; }
    int GetCurrentMP() const { return currentMP; }
    int GetMaxMP() const { return maxMP; }

    int GetStrength() const { return strength; }
    int GetAgility() const { return agility; }
    int GetIntellect() const { return intellect; }
    int GetFocus() const { return focus; }

    int GetLevel() const { return level; }
    int GetCurrentXP() const { return currentXP; }
    int GetXPToNextLevel() const { return xpToNextLevel; }
    int GetUnspentPoints() const { return unspentAttributePoints; }
    int GetRelicShards() const { return relicShards; }
};
//Organized and Refactored