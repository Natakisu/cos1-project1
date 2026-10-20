#pragma once
#include <string>
#include "Weapon.h"
#include <fstream>

class Enemy; // Fix Sytax Error

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

public:
    Player(std::string name);
    ~Player();

    // Setup & Progression
    void AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints);
    void RecalculatePools();
    void EquipWeapons(Weapon* primary, Weapon* secondary);

    // Actions
    bool SwapWeapon();
    int PerformLightAttack(Enemy& target);
    int PerformHeavyAttack(Enemy& target);
    void Block();
    void Dodge();
    void RegainResourcesPerTurn();

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
    void LevelUp();
    int GetLevel() const { return level; }
    int GetUnspentPoints() const { return unspentAttributePoints; }
    void AllocateAttribute(int choice, int amount);

    void UpdateDerivedStats()
    {
        maxHP = 100 + (constitution * 10);
        maxSP = 100 + (agility * 5);
        maxMP = 100 + (intellect * 5);
    }

    // Save/Load
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
};