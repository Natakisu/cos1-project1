#pragma once
#include "Player.h"
#include "Enemy.h"

class WeaponSkillManager
{
public:
    static void ExecuteSkill(Player* player, bool isLongSkill, Enemy& target);
};