#pragma once
#include <string>
#include <vector>
#include "Weapon.h"
#include "Item.h"

class Enemy;

class Player
{
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
    bool isDodging;

    // XP System
    int level;
    int currentXP;
    int xpToNextLevel;
    int unspentAttributePoints;

    // Item System
    std::vector<Item*> inventory;

    // Currency
    int relicShards;

public:
    Player(std::string name);
    ~Player();

    // Setup & Progression
    void AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints);
    void RecalculatePools();
    void UpdateDerivedStats();
    void EquipWeapons(Weapon* primary, Weapon* secondary);

    // Actions
    bool SwapWeapon();
    void UseItem(int index);
    int PerformLightAttack(Enemy& target);
    int PerformHeavyAttack(Enemy& target);
    void Block();
    void Dodge();
    void RegainResourcesPerTurn();
    void ConsumeMP(int amount) { currentMP -= amount; if (currentMP < 0) currentMP = 0; }

    // Damage & Status Handlers
    void TakeDamage(int damage);

    // Getters
    std::string GetName() const { return name; }
    int GetCurrentHP() const { return currentHP; }
    int GetCurrentSP() const { return currentSP; }
    int GetCurrentMP() const { return currentMP; }
    int GetMaxHP() const { return maxHP; }
    int GetMaxSP() const { return maxSP; }
    int GetMaxMP() const { return maxMP; }

    Weapon* GetActiveWeapon() const { return isPrimaryActive ? primaryWeapon : secondaryWeapon; }
    bool IsAlive() const { return currentHP > 0; }

    void SetAttributes(int con, int str, int agi, int intel, int foc);
    void DisplayStats() const;

    void InspectWeapons() const;

    // XP System
    void GainXP(int amount);
    int GetLevel() const { return level; }
    int GetUnspentPoints() const { return unspentAttributePoints; }
    void AddUnspentPoints(int amount) { unspentAttributePoints += amount; }
    void AllocateAttribute(int choice, int amount);
    int GetCurrentXP() const { return currentXP; }
    int GetXPToNextLevel() const { return xpToNextLevel; }

    // Save/Load
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);

    // Item System
    void AddItem(Item* item);
    void UseItem(size_t index);
    void CastMagicBlessing(Item* item, Enemy* target);
    void UseItem(Item* item);
    const std::vector<Item*>& GetInventory() const;

    // Currency
    int GetRelicShards() const { return relicShards; }
    void AddRelicShards(int amount) { relicShards += amount; }
    void SpendRelicShards(int amount) { if (relicShards >= amount) relicShards -= amount; }

};