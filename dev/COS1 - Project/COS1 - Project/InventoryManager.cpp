#include "Player.h"
#include "Enemy.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <algorithm>

InventoryManager::InventoryManager() = default;

InventoryManager::~InventoryManager()
{
    ClearInventory();
}

void InventoryManager::ClearInventory()
{
    for (Item* item : inventory)
    {
        delete item;
    }
    inventory.clear();
}

void InventoryManager::AddItem(Item* item)
{
    inventory.push_back(item);
}

const std::vector<Item*>& InventoryManager::GetInventory() const
{
    return inventory;
}

void InventoryManager::UseItem(int index, Player* player)
{
    if (index < 0 || index >= static_cast<int>(inventory.size())) return;

    Item* item = inventory[index];
    if (!item) return;

    if (item->GetType() == ItemType::HealthPotion)
    {
        player->RestoreHP(item->GetEffectValue()); // Assuming we add a helper or update stats
        std::cout << " > Used " << item->GetName() << "! Restored " << item->GetEffectValue() << " HP.\n";
    }
    else if (item->GetType() == ItemType::StaminaPotion)
    {
        player->RestoreSP(item->GetEffectValue());
        std::cout << " > Used " << item->GetName() << "! Restored " << item->GetEffectValue() << " Stamina.\n";
    }
    else if (item->GetType() == ItemType::ManaPotion)
    {
        player->RestoreMP(item->GetEffectValue());
        std::cout << " > Used " << item->GetName() << "! Restored " << item->GetEffectValue() << " Mana.\n";
    }
}

void InventoryManager::CastMagicBlessing(Item* item, Player* player, Enemy* target)
{
    if (!item || !target || !player) return;

    int manaCost = 100;
    if (player->GetCurrentMP() < manaCost)
    {
        std::cout << " > Not enough Mana to cast " << item->GetName() << "! (Requires 100 MP)\n";
        return;
    }

    player->ConsumeMP(manaCost);

    if (item->GetType() == ItemType::DinsFire)
    {
        target->TakeDamage(45, 15);
        target->ApplyStatusBuildup(0, 50, 0);
        std::cout << " > You cast Din's Fire! Flames engulf the foe, causing intense Burn buildup.\n";
    }
    else if (item->GetType() == ItemType::FaroresWind)
    {
        target->TakeDamage(35, 15);
        target->ApplyStatusBuildup(50, 0, 0);
        std::cout << " > You cast Farore's Wind! Gale-force winds slash the foe, causing severe Bleed buildup.\n";
    }
    else if (item->GetType() == ItemType::NayrusLove)
    {
        target->TakeDamage(35, 15);
        target->ApplyStatusBuildup(0, 0, 50);
        std::cout << " > You cast Nayru's Love! Crystal energy freezes the foe, causing heavy Frostbite buildup.\n";
    }
}