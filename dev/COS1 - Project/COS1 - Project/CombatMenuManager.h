#pragma once
#include "Player.h"
#include "Enemy.h"

class CombatMenuManager
{
public:
    // Renders and handles the inventory and magic spell casting menu during combat
    static bool HandleInventoryMenu(Player* player, Enemy* target);

    // Renders and handles the weapon short/long skill selection menu
    static bool HandleWeaponSkillMenu(Player* player, Enemy* target);
};