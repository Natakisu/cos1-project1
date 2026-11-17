#include "PlayerSaveManager.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include <fstream>
#include <iostream>

void PlayerSaveManager::Save(const Player* player, const std::string& filename)
{
    std::ofstream outFile(filename);
    if (outFile.is_open())
    {
        outFile << player->GetName() << "\n";
        outFile << player->GetLevel() << "\n";
        outFile << player->GetCurrentXP() << "\n";
        outFile << player->GetXPToNextLevel() << "\n";
        outFile << player->GetMaxHP() << "\n";
        outFile << player->GetCurrentHP() << "\n";
        outFile << player->constitution << "\n";
        outFile << player->strength << "\n";
        outFile << player->agility << "\n";
        outFile << player->intellect << "\n";
        outFile << player->focus << "\n";
        outFile << player->GetUnspentPoints() << "\n";
        outFile << player->GetRelicShards() << "\n";

        const auto& inventory = player->GetInventory();
        outFile << inventory.size() << "\n";
        for (const Item* item : inventory)
        {
            if (item)
            {
                outFile << static_cast<int>(item->GetType()) << "\n";
                outFile << item->GetName() << "\n";
                outFile << item->GetEffectValue() << "\n";
                outFile << item->GetCost() << "\n";
            }
        }

        outFile.close();
        ConsoleHelper::print("[!] Game saved successfully!", ConsoleHelper::Green);
    }
    else
    {
        ConsoleHelper::print("[!] Error: Could not open file for saving.", ConsoleHelper::Red);
    }
}

void PlayerSaveManager::Load(Player* player, const std::string& filename)
{
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        std::getline(inFile, player->name);
        inFile >> player->level;
        inFile >> player->currentXP;
        inFile >> player->xpToNextLevel;
        inFile >> player->maxHP;
        inFile >> player->currentHP;
        inFile >> player->constitution;
        inFile >> player->strength;
        inFile >> player->agility;
        inFile >> player->intellect;
        inFile >> player->focus;
        inFile >> player->unspentAttributePoints;
        inFile >> player->relicShards;

        player->GetInventoryManager().ClearInventory();

        size_t inventorySize = 0;
        inFile >> inventorySize;
        inFile.ignore();

        for (size_t i = 0; i < inventorySize; ++i)
        {
            int typeInt = 0;
            std::string itemName;
            int effectVal = 0;
            int itemCost = 0;

            inFile >> typeInt;
            inFile.ignore();
            std::getline(inFile, itemName);
            inFile >> effectVal >> itemCost;
            inFile.ignore();

            ItemType type = static_cast<ItemType>(typeInt);
            player->AddItem(new Item(itemName, type, effectVal, itemCost));
        }

        inFile.close();
        player->UpdateDerivedStats();

        ConsoleHelper::print("[!] Game loaded successfully!", ConsoleHelper::Green);
    }
    else
    {
        ConsoleHelper::print("[!] Error: No save file found. Starting fresh.", ConsoleHelper::Yellow);
    }
}
