#include "Item.h"
#include "ConsoleHelper.h"
#include <iostream>

// --- CONSTRUCTORS ---
Item::Item(std::string itemName, ItemType itemType, int value, int itemCost)
    : name(itemName), type(itemType), effectValue(value), cost(itemCost)
{
}

// --- GETTERS ---
std::string Item::GetName() const { return name; }
ItemType Item::GetType() const { return type; }
int Item::GetEffectValue() const { return effectValue; }
int Item::GetCost() const { return cost; }

// --- UI & DISPLAY ---
void Item::DisplayInfo() const
{
    std::string typeStr = "[Misc]";
    if (type == ItemType::HealthPotion) typeStr = "[Health Potion]";
    else if (type == ItemType::StaminaPotion) typeStr = "[SP Potion]";
    else if (type == ItemType::ManaPotion) typeStr = "[MP Potion]";

    ConsoleHelper::print(typeStr + " " + name + " (Value: +" + std::to_string(effectValue) + ")", ConsoleHelper::White);
}
//Organized and Refactored