#include "Item.h"
#include "ConsoleHelper.h"
#include <iostream>

Item::Item(std::string itemName, ItemType itemType, int itemPotency, int itemPrice)
    : name(itemName), type(itemType), potency(itemPotency), price(itemPrice) {
}

std::string Item::GetName() const { return name; }
ItemType Item::GetType() const { return type; } 
int Item::GetPotency() const { return potency; }
int Item::GetPrice() const { return price; }

void Item::DisplayItemInfo() const {
    ConsoleHelper::print(name + " (Potency: " + std::to_string(potency) + ") - Cost: " + std::to_string(price) + " Shards", ConsoleHelper::White);
}