#include "Item.h"
#include "ConsoleHelper.h"
#include <iostream>

Item::Item(std::string itemName, ItemType itemType, int value, int itemCost)
    : name(itemName), type(itemType), effectValue(value), cost(itemCost)
{
}

std::string Item::GetName() const
{
    return name;
}

ItemType Item::GetType() const
{
    return type;
}

int Item::GetEffectValue() const
{
    return effectValue;
}

int Item::GetCost() const
{
    return cost;
}

void Item::DisplayInfo() const
{
    std::string typeStr = "[Misc]";
    if (type == ItemType::HealthPotion) typeStr = "[Health Potion]";
    else if (type == ItemType::StaminaPotion) typeStr = "[SP Potion]";
    else if (type == ItemType::ManaPotion) typeStr = "[MP Potion]";

    ConsoleHelper::print(typeStr + " " + name + " (Value: +" + std::to_string(effectValue) + ")", ConsoleHelper::White);
}