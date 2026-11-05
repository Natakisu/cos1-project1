#pragma once
#include <string>

enum class ItemType { HealthPotion, StaminaPotion, StatusCleanser };

class Item {
private:
    std::string name;
    ItemType type;
    int potency;
    int price;

public:
    Item(std::string itemName, ItemType itemType, int itemPotency, int itemPrice);

    std::string GetName() const;
    ItemType GetType() const;
    int GetPotency() const;
    int GetPrice() const;

    void DisplayItemInfo() const;
};