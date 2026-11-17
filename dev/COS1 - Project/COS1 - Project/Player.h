#pragma once
#include <string>
#include <algorithm>
#include "Weapon.h"
#include "Item.h"
#include "InventoryManager.h"

class Enemy;

class Player
{
private:

    friend class PlayerSaveManager;
    friend class WeaponSkillManager;

    std::string name;

    // Attributes
    int constitution;
    int strength;
    int agility;
    int intellect;
    int focus;

    // Resource Pools
    int maxHP;
    int currentHP;
    int maxSP;
    int currentSP;
    int maxMP;
    int currentMP;

    // Equipment & Combat State
    Weapon* primaryWeapon;
    Weapon* secondaryWeapon;
    bool isPrimaryActive;
    bool isBlocking;
    bool isFullBlocking;
    bool isDodging;

    // Progression & Economy
    int level;
    int currentXP;
    int xpToNextLevel;
    int unspentAttributePoints;
    int relicShards;

    // Delegated Inventory Manager
    InventoryManager inventoryManager;

    void RecalculatePools();

    friend class PlayerSaveManager;

public:
    // --- CONSTRUCTORS & DESTRUCTOR ---
    Player(std::string name = "Hero");
    ~Player();

    // --- ATTRIBUTES & POOL MANAGEMENT ---
    void AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints);
    void SetAttributes(int con, int str, int agi, int intel, int foc);
    void AllocateAttribute(int choice, int amount);
    void DisplayStats() const;
    void UpdateDerivedStats();

    // --- WEAPONS & LOADOUT ---
    void EquipWeapons(Weapon* primary, Weapon* secondary);
    void InspectWeapons() const;
    bool SwapWeapon();
    bool ExecuteWeaponSkill(bool isLongSkill, Enemy& target);

    Weapon* GetActiveWeapon() const { return isPrimaryActive ? primaryWeapon : secondaryWeapon; }
    Weapon* GetPrimaryWeapon() const { return primaryWeapon; }
    Weapon* GetSecondaryWeapon() const { return secondaryWeapon; }

    // --- INVENTORY DELEGATION ---
    void AddItem(Item* item) { inventoryManager.AddItem(item); }
    const std::vector<Item*>& GetInventory() const { return inventoryManager.GetInventory(); }
    void UseItem(int index) { inventoryManager.UseItem(index, this); }
    void CastMagicBlessing(Item* item, Enemy* target) { inventoryManager.CastMagicBlessing(item, this, target); }
    InventoryManager& GetInventoryManager() { return inventoryManager; }

    // --- COMBAT ACTIONS & RESOURCE MANAGEMENT ---
    int PerformLightAttack(Enemy& target);
    int PerformHeavyAttack(Enemy& target);
    void Block();
    void Dodge();
    void RegainResourcesPerTurn();
    void TakeDamage(int damage);

    void RestoreHP(int amount) { currentHP = std::min(maxHP, currentHP + amount); }
    void RestoreSP(int amount) { currentSP = std::min(maxSP, currentSP + amount); }
    void RestoreMP(int amount) { currentMP = std::min(maxMP, currentMP + amount); }
    void ConsumeMP(int amount) { currentMP = std::max(0, currentMP - amount); }
    void ConsumeSP(int amount) { currentSP = std::max(0, currentSP - amount); }
    void FullBlock() { isFullBlocking = true; }
    void Heal(int amount) { currentHP = std::min(maxHP, currentHP + amount); }
    void AddUnspentPoints(int amount) { unspentAttributePoints += amount; }

    void SetFullBlocking(bool state) { isFullBlocking = state; }
    void SetDodging(bool state) { isDodging = state; }

    // --- PROGRESSION & REWARDS ---
    void GainXP(int amount);
    void AddRelicShards(int amount) { relicShards += amount; }
    bool SpendRelicShards(int amount) {
        if (relicShards < amount) return false;
        relicShards -= amount;
        return true;
    }

    // --- SAVE & LOAD OPERATIONS ---
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void AutoSave() const { SaveToFile(name + "_save.txt"); }

    // --- GETTERS ---
    std::string GetName() const { return name; }
    int GetLevel() const { return level; }
    int GetCurrentXP() const { return currentXP; }
    int GetXPToNextLevel() const { return xpToNextLevel; }
    int GetUnspentPoints() const { return unspentAttributePoints; }
    int GetRelicShards() const { return relicShards; }

    int GetMaxHP() const { return maxHP; }
    int GetCurrentHP() const { return currentHP; }
    int GetMaxSP() const { return maxSP; }
    int GetCurrentSP() const { return currentSP; }
    int GetMaxMP() const { return maxMP; }
    int GetCurrentMP() const { return currentMP; }

    int GetConstitution() const { return constitution; }
    int GetStrength() const { return strength; }
    int GetAgility() const { return agility; }
    int GetIntellect() const { return intellect; }
    int GetFocus() const { return focus; }

    bool IsAlive() const { return currentHP > 0; }
};