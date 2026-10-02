#pragma once
#include <string>
#include "Weapon.h"

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
    Weapon* GetActiveWeapon() const { return isPrimaryActive ? primaryWeapon : secondaryWeapon; }
    bool IsAlive() const { return currentHP > 0; }
};