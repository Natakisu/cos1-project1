#include "WeaponSkills.h"
#include "ConsoleHelper.h"
#include <iostream>

// --- RESOURCE VALIDATION & CONSUMPTION ---
bool WeaponSkillManager::HasEnoughResource(Player* player, int cost, bool isMana)
{
    if (isMana)
    {
        if (player->GetCurrentMP() < cost)
        {
            ConsoleHelper::print("\n[!] Not enough Mana! (Requires " + std::to_string(cost) + " MP)", ConsoleHelper::Red);
            return false;
        }
        player->ConsumeMP(cost);
    }
    else
    {
        if (player->GetCurrentSP() < cost)
        {
            ConsoleHelper::print("\n[!] Not enough Stamina! (Requires " + std::to_string(cost) + " SP)", ConsoleHelper::Red);
            return false;
        }
        player->ConsumeSP(cost);
    }
    return true;
}

// --- CENTRAL SKILL ROUTER ---
bool WeaponSkillManager::ExecuteSkill(Player* player, bool isLongSkill, Enemy& target)
{
    Weapon* activeWeapon = player->GetActiveWeapon();
    if (!activeWeapon)
    {
        ConsoleHelper::print("\n[!] No active weapon equipped!", ConsoleHelper::Red);
        return false;
    }

    if (!isLongSkill && !activeWeapon->CanUseShortSkill())
    {
        ConsoleHelper::print("\n[!] That skill is still on cooldown!", ConsoleHelper::Yellow);
        return false;
    }
    if (isLongSkill && !activeWeapon->CanUseLongSkill())
    {
        ConsoleHelper::print("\n[!] That skill is still on cooldown!", ConsoleHelper::Yellow);
        return false;
    }

    std::string wName = activeWeapon->GetName();

    if (wName == "Warhammer") return ExecuteWarhammer(player, activeWeapon, isLongSkill, target);
    if (wName == "Sword & Shield" || wName == "Sword and Shield") return ExecuteSwordAndShield(player, activeWeapon, isLongSkill, target);
    if (wName == "Daggers") return ExecuteDaggers(player, activeWeapon, isLongSkill, target);
    if (wName == "Bow") return ExecuteBow(player, activeWeapon, isLongSkill, target);
    if (wName == "Fire Staff") return ExecuteFireStaff(player, activeWeapon, isLongSkill, target);
    if (wName == "Ice Staff") return ExecuteIceStaff(player, activeWeapon, isLongSkill, target);
    if (wName == "Life Staff") return ExecuteLifeStaff(player, activeWeapon, isLongSkill, target);
    if (wName == "Greatsword") return ExecuteGreatsword(player, activeWeapon, isLongSkill, target);
    if (wName == "Rapier") return ExecuteRapier(player, activeWeapon, isLongSkill, target);
    if (wName == "Flail & Shield" || wName == "Flail and Shield") return ExecuteFlailAndShield(player, activeWeapon, isLongSkill, target);

    ConsoleHelper::print("\n[!] This weapon has no special skills defined yet.", ConsoleHelper::Yellow);
    return false;
}

// --- WEAPON-SPECIFIC SKILL IMPLEMENTATIONS ---
bool WeaponSkillManager::ExecuteWarhammer(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Crushing Blow (25 SP, 2 CD)
    {
        if (!HasEnoughResource(player, 25, false)) return false;
        int dmg = 45 + (player->strength * 2);
        target.TakeDamage(dmg, 30);
        weapon->TriggerShortSkill(2);
        std::cout << " > You unleash Crushing Blow for " << dmg << " damage and moderate posture damage!\n";
    }
    else // Earthshatter (45 SP, 4 CD)
    {
        if (!HasEnoughResource(player, 45, false)) return false;
        int dmg = 100 + (player->strength * 4);
        target.TakeDamage(dmg, 75);
        weapon->TriggerLongSkill(4);
        std::cout << " > You slam the earth with Earthshatter for " << dmg << " damage and heavy disruption!\n";
    }
    return true;
}

bool WeaponSkillManager::ExecuteSwordAndShield(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Shield Bash (20 SP, 2 CD) -> Damage + Guard
    {
        if (!HasEnoughResource(player, 20, false)) return false;
        int dmg = 25 + player->strength;
        target.TakeDamage(dmg, 40);
        player->Block();
        weapon->TriggerShortSkill(2);
        std::cout << " > You perform Shield Bash for " << dmg << " damage and raise your guard!\n";
    }
    else // Fortress Wall (35 SP, 3 CD) -> 100% Block
    {
        if (!HasEnoughResource(player, 35, false)) return false;
        player->FullBlock();
        weapon->TriggerLongSkill(3);
        ConsoleHelper::print(" > You raise Fortress Wall! Incoming damage is completely negated this turn.", ConsoleHelper::Cyan);
    }
    return true;
}

bool WeaponSkillManager::ExecuteDaggers(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Flurry Strike (20 SP, 2 CD)
    {
        if (!HasEnoughResource(player, 20, false)) return false;
        int totalDmg = (15 + (player->agility / 2)) * 3;
        target.TakeDamage(totalDmg, 10);
        target.ApplyStatusBuildup(60, 0, 0);
        weapon->TriggerShortSkill(2);
        std::cout << " > You execute Flurry Strike (3 hits) for " << totalDmg << " damage and moderate Bleed!\n";
    }
    else // Shadow Step (35 SP, 4 CD) -> Auto-Dodge + High Bleed
    {
        if (!HasEnoughResource(player, 35, false)) return false;
        player->Dodge();
        target.ApplyStatusBuildup(100, 0, 0);
        weapon->TriggerLongSkill(4);
        ConsoleHelper::print(" > You vanish into Shadow Step! Next attack will be dodged and high Bleed inflicted.", ConsoleHelper::Green);
    }
    return true;
}

bool WeaponSkillManager::ExecuteBow(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Quick Shot (15 SP, 1 CD) -> Damage + Evasive Dodge
    {
        if (!HasEnoughResource(player, 15, false)) return false;
        int dmg = 30 + player->agility;
        target.TakeDamage(dmg, 15);
        player->Dodge();
        weapon->TriggerShortSkill(1);
        std::cout << " > You fire Quick Shot for " << dmg << " damage and leap back into an evasive dodge!\n";
    }
    else // Rain of Arrows (40 SP, 4 CD)
    {
        if (!HasEnoughResource(player, 40, false)) return false;
        int dmg = 50 + (player->agility * 2);
        target.TakeDamage(dmg, 50);
        weapon->TriggerLongSkill(4);
        std::cout << " > You unleash Rain of Arrows for " << dmg << " damage and heavy posture pressure!\n";
    }
    return true;
}

bool WeaponSkillManager::ExecuteFireStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Fireball (25 MP, 2 CD)
    {
        if (!HasEnoughResource(player, 25, true)) return false;
        int dmg = 50 + (player->intellect * 2);
        target.TakeDamage(dmg, 20);
        target.ApplyStatusBuildup(0, 50, 0);
        weapon->TriggerShortSkill(2);
        std::cout << " > You cast Fireball for " << dmg << " damage and moderate Burn buildup!\n";
    }
    else // Combustion (50 MP, 4 CD)
    {
        if (!HasEnoughResource(player, 50, true)) return false;
        int burnBonus = target.GetBurnMeter() * 2;
        int dmg = 40 + (player->intellect * 2) + burnBonus;
        target.TakeDamage(dmg, 30);
        weapon->TriggerLongSkill(4);
        std::cout << " > You trigger Combustion, consuming target heat for " << dmg << " massive damage!\n";
    }
    return true;
}

bool WeaponSkillManager::ExecuteIceStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Ice Spike (20 MP, 1 CD)
    {
        if (!HasEnoughResource(player, 20, true)) return false;
        int dmg = 35 + (player->intellect * 2);
        target.TakeDamage(dmg, 20);
        target.ApplyStatusBuildup(0, 0, 50);
        weapon->TriggerShortSkill(1);
        std::cout << " > You hurl Ice Spike for " << dmg << " damage and moderate Frostbite buildup!\n";
    }
    else // Entomb (30 MP, 4 CD) -> 100% Block + MP Recovery
    {
        if (!HasEnoughResource(player, 30, true)) return false;
        int mpRecovered = 50 + (player->intellect * 2);
        player->FullBlock();
        player->RestoreMP(mpRecovered);
        weapon->TriggerLongSkill(4);
        ConsoleHelper::print(" > You cast Entomb! Encased in ice (100% block) and restored " + std::to_string(mpRecovered) + " MP.", ConsoleHelper::Cyan);
    }
    return true;
}

bool WeaponSkillManager::ExecuteLifeStaff(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Divine Plea (25 MP, 2 CD) -> Moderate Heal
    {
        if (!HasEnoughResource(player, 25, true)) return false;
        int healAmount = 45 + (player->focus * 3);
        player->Heal(healAmount);
        weapon->TriggerShortSkill(2);
        ConsoleHelper::print(" > You offer Divine Plea, restoring " + std::to_string(healAmount) + " HP!", ConsoleHelper::Green);
    }
    else // Sacred Ground (45 MP, 4 CD) -> Large Heal + Defensive Guard
    {
        if (!HasEnoughResource(player, 45, true)) return false;
        int healAmount = 80 + (player->focus * 4);
        player->Heal(healAmount);
        player->Block();
        weapon->TriggerLongSkill(4);
        ConsoleHelper::print(" > You consecrate Sacred Ground, restoring " + std::to_string(healAmount) + " HP and raising your guard!", ConsoleHelper::Green);
    }
    return true;
}

bool WeaponSkillManager::ExecuteGreatsword(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Relentless Onslaught (25 SP, 2 CD)
    {
        if (!HasEnoughResource(player, 25, false)) return false;
        int hits = 2 + (player->agility / 15);
        int totalDmg = hits * (20 + (player->strength / 2));
        target.TakeDamage(totalDmg, 40);
        weapon->TriggerShortSkill(2);
        std::cout << " > You launch Relentless Onslaught (" << hits << " hits) for " << totalDmg << " total damage!\n";
    }
    else // Execute (45 SP, 4 CD)
    {
        if (!HasEnoughResource(player, 45, false)) return false;
        int dmg = 80 + (player->strength * 4);
        target.TakeDamage(dmg, 90);
        weapon->TriggerLongSkill(4);
        std::cout << " > You deliver a devastating Execute strike for " << dmg << " damage!\n";
    }
    return true;
}

bool WeaponSkillManager::ExecuteRapier(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Evade Stance (20 SP, 2 CD) -> Bleed-scaling strike + Dodge
    {
        if (!HasEnoughResource(player, 20, false)) return false;
        int dmg = 20 + player->agility + (target.GetBleedMeter() / 2);
        target.TakeDamage(dmg, 20);
        player->Dodge();
        weapon->TriggerShortSkill(2);
        std::cout << " > You enter Evade Stance, striking for " << dmg << " damage and preparing to dodge!\n";
    }
    else // Detonate Stance (25 SP, 2 CD) -> Burn-scaling strike + MP Regen
    {
        if (!HasEnoughResource(player, 25, false)) return false;
        int dmg = 30 + player->intellect + (target.GetBurnMeter() / 2);
        int mpRegen = 25 + player->intellect;
        target.TakeDamage(dmg, 30);
        player->RestoreMP(mpRegen);
        weapon->TriggerLongSkill(2);
        std::cout << " > You trigger Detonate Stance for " << dmg << " damage and regenerate " << mpRegen << " MP!\n";
    }
    return true;
}

bool WeaponSkillManager::ExecuteFlailAndShield(Player* player, Weapon* weapon, bool isLongSkill, Enemy& target)
{
    if (!isLongSkill) // Blessed Aegis (20 SP, 2 CD) -> Block + Focus Heal
    {
        if (!HasEnoughResource(player, 20, false)) return false;
        int healAmount = 25 + (player->focus * 2);
        player->Block();
        player->Heal(healAmount);
        weapon->TriggerShortSkill(2);
        ConsoleHelper::print(" > You raise Blessed Aegis, blocking incoming damage and restoring " + std::to_string(healAmount) + " HP!", ConsoleHelper::Green);
    }
    else // Divine Smite (35 SP + 20 MP, 4 CD) -> Heavy Damage + Health Pulse
    {
        if (!HasEnoughResource(player, 35, false)) return false;
        int dmg = 70 + player->strength + player->focus;
        int healPulse = 30 + (player->focus * 2);
        target.TakeDamage(dmg, 60);
        player->Heal(healPulse);
        weapon->TriggerLongSkill(4);
        ConsoleHelper::print(" > You unleash Divine Smite for " + std::to_string(dmg) + " damage and pulse " + std::to_string(healPulse) + " HP!", ConsoleHelper::Green);
    }
    return true;
}
//Organized and Refactored