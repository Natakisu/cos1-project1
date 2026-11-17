#pragma once
#include "Player.h"
#include "Enemy.h"

class WeaponSkillManager
{
private:
    // --- RESOURCE VALIDATION ---
    static bool HasEnoughResource(Player* player, int cost, bool isMana);

    // --- WEAPON-SPECIFIC SKILL HANDLERS ---
    static bool ExecuteWarhammer(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteSwordAndShield(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteDaggers(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteBow(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteFireStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteIceStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteLifeStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteGreatsword(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteRapier(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);
    static bool ExecuteFlailAndShield(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target);

public:
    // --- PUBLIC SKILL INTERFACE ---

    // Returns true if skill successfully executed (consumes turn), false otherwise
    static bool ExecuteSkill(Player* player, bool isLongSkill, Enemy& target);
};
//Organized and Refactored