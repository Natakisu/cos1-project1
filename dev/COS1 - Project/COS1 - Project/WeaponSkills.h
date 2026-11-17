#pragma once
#include "Player.h"
#include "Enemy.h"

class WeaponSkillManager
{
public:
    // Executes the active weapon's short or long skill against the target enemy
    static void ExecuteSkill(Player* player, bool isLongSkill, Enemy& target);
};