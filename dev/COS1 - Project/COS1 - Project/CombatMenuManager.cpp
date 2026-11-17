#include "CombatMenuManager.h"
#include "ConsoleHelper.h"
#include "GameInput.h"
#include <iostream>
#include <cstdlib>

bool CombatMenuManager::HandleInventoryMenu(Player* player, Enemy* target)
{
    const auto& inv = player->GetInventory();
    if (inv.empty())
    {
        ConsoleHelper::print("\n[!] Your inventory is completely empty!", ConsoleHelper::Yellow);
        return false;
    }

    ConsoleHelper::print("\n==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("          [ INVENTORY ]           ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    for (size_t i = 0; i < inv.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        inv[i]->DisplayInfo();
    }
    ConsoleHelper::print("0. Back to Combat", ConsoleHelper::White);
    ConsoleHelper::print("==================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Select item/spell to use (0 to cancel): ", ConsoleHelper::Cyan, false);

    int itemChoice = GameInput::GetValidatedChoice(0, (int)inv.size());
    if (itemChoice == 0) return false;

    Item* chosenItem = inv[itemChoice - 1];
    ItemType type = chosenItem->GetType();

    if (type == ItemType::DinsFire || type == ItemType::FaroresWind || type == ItemType::NayrusLove)
    {
        if (player->GetCurrentMP() < 100)
        {
            ConsoleHelper::print("\n[!] Not enough Mana to cast " + chosenItem->GetName() + "! (Requires 100 MP)", ConsoleHelper::Red);
            return false;
        }
        player->ConsumeMP(100);

        if (type == ItemType::DinsFire)
        {
            target->TakeDamage(45, 15);
            target->ApplyStatusBuildup(0, 75, 0);
            ConsoleHelper::print("\n > You cast Din's Fire! Intense Burn applied.", ConsoleHelper::Red);
        }
        else if (type == ItemType::FaroresWind)
        {
            target->TakeDamage(35, 20);
            target->ApplyStatusBuildup(75, 0, 0);
            ConsoleHelper::print("\n > You cast Farore's Wind! Severe Bleed applied.", ConsoleHelper::Green);
        }
        else if (type == ItemType::NayrusLove)
        {
            target->TakeDamage(35, 25);
            target->ApplyStatusBuildup(0, 0, 75);
            ConsoleHelper::print("\n > You cast Nayru's Love! Heavy Frostbite applied.", ConsoleHelper::Cyan);
        }
    }
    else
    {
        player->UseItem(itemChoice - 1);
    }
    return true;
}

bool CombatMenuManager::HandleWeaponSkillMenu(Player* player, Enemy* target)
{
    Weapon* activeWeapon = player->GetActiveWeapon();
    if (!activeWeapon)
    {
        ConsoleHelper::print("\n[!] No active weapon equipped!", ConsoleHelper::Red);
        return false;
    }

    system("cls");
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("             [ WEAPON SKILLS: " + activeWeapon->GetName() + " ]       ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);

    int shortCD = activeWeapon->GetShortCooldownRemaining();
    int longCD = activeWeapon->GetLongCooldownRemaining();

    std::cout << "1. Short Skill";
    if (shortCD == 0) ConsoleHelper::print(" [READY]", ConsoleHelper::Green);
    else std::cout << " [CD: " << shortCD << " turns]\n";

    std::cout << "2. Long Skill";
    if (longCD == 0) ConsoleHelper::print(" [READY]", ConsoleHelper::Green);
    else std::cout << " [CD: " << longCD << " turns]\n";

    ConsoleHelper::print("0. Back", ConsoleHelper::White);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("Select skill (0-2): ", ConsoleHelper::Cyan, false);

    int skillChoice = GameInput::GetValidatedChoice(0, 2);
    if (skillChoice == 0) return false;

    bool isLong = (skillChoice == 2);
    bool success = player->ExecuteWeaponSkill(isLong, *target);

    if (success)
    {
        if (std::cin.peek() == '\n') std::cin.ignore();
        ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::Cyan, false);
        std::string dummy;
        std::getline(std::cin, dummy);
    }
    return success;
}
