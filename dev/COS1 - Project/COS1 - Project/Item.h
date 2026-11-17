#pragma once
#include <string>

// --- ITEM TYPES ---
enum class ItemType
{
    HealthPotion,
    StaminaPotion,
    ManaPotion,
    DinsFire,
    FaroresWind,
    NayrusLove,
    Weapon,
    Misc
};

class Item
{
private:
    std::string name;
    ItemType type;
    int effectValue;
    int cost;

public:
    // --- CONSTRUCTORS ---
    Item(std::string itemName, ItemType itemType, int value, int itemCost);

    // --- GETTERS ---
    std::string GetName() const;
    ItemType GetType() const;
    int GetEffectValue() const;
    int GetCost() const;

    // --- DISPLAY UTILITIES ---
    void DisplayInfo() const;
};
//Organized and Refactored