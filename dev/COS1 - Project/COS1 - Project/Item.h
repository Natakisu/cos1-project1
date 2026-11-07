#pragma once
#include <string>

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
    Item(std::string itemName, ItemType itemType, int value, int itemCost);

    std::string GetName() const;
    ItemType GetType() const;
    ItemType GetPotency() const;
    int GetEffectValue() const;
    int GetCost() const;

    void DisplayInfo() const;
};