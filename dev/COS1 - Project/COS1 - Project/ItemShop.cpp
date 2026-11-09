#include "ItemShop.h"
#include "GameInput.h"
#include "ConsoleHelper.h"
#include "Item.h"
#include <iostream>
#include <cstdlib>

void ItemShop::Open(Player* player)
{
    if (!player) return;

    bool shopping = true;

    while (shopping)
    {
        system("cls");
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("       [ RELIC ITEM SHOP ]        ", ConsoleHelper::Cyan);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print(" Shards Available: " + std::to_string(player->GetRelicShards()) + "rs", ConsoleHelper::Purple);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("1. Health Potion (Restores Health)", ConsoleHelper::White);
        ConsoleHelper::print("   Cost: 35rs", ConsoleHelper::Purple);
        ConsoleHelper::print("2. SP Potion     (Restores Stamina)",ConsoleHelper::White);
        ConsoleHelper::print("   Cost: 30rs", ConsoleHelper::Purple);
        ConsoleHelper::print("3. MP Potion     (Restores mana)", ConsoleHelper::White);
        ConsoleHelper::print("   Cost: 30rs", ConsoleHelper::Purple);
        ConsoleHelper::print("4. Buy Din's Fire    (Inflicts Burn Damage)", ConsoleHelper::Red);
        ConsoleHelper::print("   Cost: 500rs", ConsoleHelper::Purple);
        ConsoleHelper::print("5. Buy Farore's Wind (Inflicts Bleed)", ConsoleHelper::Green);
        ConsoleHelper::print("   Cost: 500rs", ConsoleHelper::Purple);
        ConsoleHelper::print("6. Buy Nayru's Love  (Inflicts Frostbite)", ConsoleHelper::Blue);
        ConsoleHelper::print("   Cost: 500rs", ConsoleHelper::Purple);
        ConsoleHelper::print("----------------------------------", ConsoleHelper::Cyan);
        ConsoleHelper::print("0. Return to Preparation Hub", ConsoleHelper::White);
        ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("Select an option (0-3): ", ConsoleHelper::Cyan, false);

        int choice = GameInput::GetValidatedChoice(0, 6);

        if (choice == 0)
        {
            shopping = false;
        }
        else
        {
            std::string itemName = "";
            ItemType type = ItemType::HealthPotion;
            int healValue = 0;
            int cost = 30;

            if (choice == 1)
            {
                itemName = "Health Potion";
                type = ItemType::HealthPotion;
                healValue = 50;
                cost = 35;
            }
            else if (choice == 2)
            {
                itemName = "SP Potion";
                type = ItemType::StaminaPotion;
                healValue = 30;
                cost = 30;
            }
            else if (choice == 3)
            {
                itemName = "MP Potion";
                type = ItemType::ManaPotion;
                healValue = 30;
                cost = 30;
            }
            else if (choice == 4)
            {
                itemName = "Din's Fire";
                type = ItemType::DinsFire;
                healValue = 30;
                cost = 500;
            }
            else if (choice == 5)
            {
                itemName = "Farore's Wind";
                type = ItemType::FaroresWind;
                healValue = 30;
                cost = 500;
            }
            else if (choice == 6)
            {
                itemName = "Nayru's Love";
                type = ItemType::NayrusLove;
                healValue = 30;
                cost = 500;
            }
            
            if (player->GetRelicShards() >= cost)
            {
                player->SpendRelicShards(cost);
                player->AddItem(new Item(itemName, type, healValue, 20));

                ConsoleHelper::print("\n[+] Successfully purchased " + itemName + "!", ConsoleHelper::Green);
            }
            else
            {
                ConsoleHelper::print("\n[!] Not enough Relic Shards!", ConsoleHelper::Red);
            }

            ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }
}