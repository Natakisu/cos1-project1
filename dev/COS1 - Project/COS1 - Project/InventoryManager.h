#pragma once
#include <vector>
#include "Item.h"

class Player;
class Enemy;

class InventoryManager
{
private:
    std::vector<Item*> inventory;

public:
    InventoryManager();
    ~InventoryManager();

    // --- INVENTORY OPERATIONS ---
    void AddItem(Item* item);
    const std::vector<Item*>& GetInventory() const;
    void UseItem(int index, Player* player);
    void CastMagicBlessing(Item* item, Player* player, Enemy* target);

    // Clear/Cleanup
    void ClearInventory();
};