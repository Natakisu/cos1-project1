#include "WeaponSkills.h"
#include "ConsoleHelper.h"
#include <iostream>

void WeaponSkillManager::ExecuteSkill(Player* player, bool isLongSkill, Enemy& target)
{
    Weapon* activeWeapon = player->GetActiveWeapon();
    if (!activeWeapon)
    {
        ConsoleHelper::print("\n[!] No active weapon equipped!", ConsoleHelper::Red);
        return;
    }

    std::string wName = activeWeapon->GetName();
    int strength = player->strength;
    int agility = player->agility;
    int intellect = player->intellect;
    int focus = player->focus;

    // WARHAMMER [STR]
    if (wName == "Warhammer")
    {
        if (!isLongSkill) // Short: Crushing Blow (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Crushing Blow is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 45 + (strength * 2);
            target.TakeDamage(dmg, 30);
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You unleash Crushing Blow for " << dmg << " damage and moderate posture damage!\n";
        }
        else // Long: Earthshatter (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Earthshatter is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 100 + (strength * 4);
            target.TakeDamage(dmg, 75);
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You slam the earth with Earthshatter, dealing massive damage and disrupting the foe!\n";
        }
    }

    // SWORD & SHIELD [STR]
    else if (wName == "Sword & Shield" || wName == "Sword and Shield" || wName == "Sword &amp; Shield")
    {
        if (!isLongSkill) // Short: Shield Bash (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Shield Bash is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 25 + strength;
            target.TakeDamage(dmg, 40);
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You perform a Shield Bash, striking the foe and guarding your posture!\n";
        }
        else // Long: Fortress Wall (3 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Fortress Wall is on cooldown!", ConsoleHelper::Yellow); return; }
            activeWeapon->TriggerLongSkill(3);
            std::cout << " > You raise a Fortress Wall! 100% block active, no SP consumed for blocking.\n";
        }
    }

    // DAGGERS [AGI]
    else if (wName == "Daggers")
    {
        if (!isLongSkill) // Short: Flurry Strike (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Flurry Strike is on cooldown!", ConsoleHelper::Yellow); return; }
            int hitDmg = 15 + (agility / 2);
            int totalDmg = hitDmg * 3;
            target.TakeDamage(totalDmg, 10);
            target.ApplyStatusBuildup(60, 0, 0); // Moderate Bleed
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You execute Flurry Strike (3 hits) for " << totalDmg << " total damage and apply moderate Bleed!\n";
        }
        else // Long: Shadow Step (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Shadow Step is on cooldown!", ConsoleHelper::Yellow); return; }
            target.ApplyStatusBuildup(100, 0, 0); // High Bleed
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You use Shadow Step, vanishing into the shadows and inflicting high Bleed!\n";
        }
    }

    // BOW [AGI]
    else if (wName == "Bow")
    {
        if (!isLongSkill) // Short: Quick Shot (1 Turn)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Quick Shot is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 30 + agility;
            target.TakeDamage(dmg, 15);
            activeWeapon->TriggerShortSkill(1);
            std::cout << " > You fire a Quick Shot for " << dmg << " damage!\n";
        }
        else // Long: Rain of Arrows (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Rain of Arrows is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 50 + (agility * 2);
            target.TakeDamage(dmg, 50);
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You unleash a Rain of Arrows, dealing consistent damage and posture pressure!\n";
        }
    }

    // FIRE STAFF [INT]
    else if (wName == "Fire Staff")
    {
        if (!isLongSkill) // Short: Fireball (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Fireball is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 50 + (intellect * 2);
            target.TakeDamage(dmg, 20);
            target.ApplyStatusBuildup(0, 50, 0); // Moderate Burn
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You cast Fireball for " << dmg << " damage and moderate Burn buildup!\n";
        }
        else // Long: Combustion (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Combustion is on cooldown!", ConsoleHelper::Yellow); return; }
            int burnBonus = target.GetBurnMeter() * 2;
            int dmg = 40 + (intellect * 2) + burnBonus;
            target.TakeDamage(dmg, 30);
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You trigger Combustion, consuming target heat for " << dmg << " massive damage!\n";
        }
    }

    // ICE STAFF [INT]
    else if (wName == "Ice Staff")
    {
        if (!isLongSkill) // Short: Ice Spike (1 Turn)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Ice Spike is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 35 + (intellect * 2);
            target.TakeDamage(dmg, 20);
            target.ApplyStatusBuildup(0, 0, 50); // Moderate Frostbite
            activeWeapon->TriggerShortSkill(1);
            std::cout << " > You hurl an Ice Spike for " << dmg << " damage and moderate Frostbite buildup!\n";
        }
        else // Long: Entomb (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Entomb is on cooldown!", ConsoleHelper::Yellow); return; }
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You cast Entomb, encasing yourself in ice!\n";
        }
    }

    // LIFE STAFF [FOC]
    else if (wName == "Life Staff")
    {
        if (!isLongSkill) // Short: Divine Plea (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Divine Plea is on cooldown!", ConsoleHelper::Yellow); return; }
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You offer a Divine Plea!\n";
        }
        else // Long: Sacred Ground (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Sacred Ground is on cooldown!", ConsoleHelper::Yellow); return; }
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You consecrate Sacred Ground!\n";
        }
    }

    // GREATSWORD [STR / AGI]
    else if (wName == "Greatsword")
    {
        if (!isLongSkill) // Short: Relentless Onslaught (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Relentless Onslaught is on cooldown!", ConsoleHelper::Yellow); return; }
            int hits = 2 + (agility / 15);
            int totalDmg = hits * (20 + (strength / 2));
            target.TakeDamage(totalDmg, 40);
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You launch a Relentless Onslaught (" << hits << " hits) for " << totalDmg << " total damage!\n";
        }
        else // Long: Execute (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Execute is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 80 + (strength * 4);
            target.TakeDamage(dmg, 90);
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You deliver a devastating Execute strike for " << dmg << " damage!\n";
        }
    }

    // RAPIER [AGI / INT]
    else if (wName == "Rapier")
    {
        if (!isLongSkill) // Short: Evade Stance (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Evade Stance is on cooldown!", ConsoleHelper::Yellow); return; }
            int bleedBonus = target.GetBleedMeter();
            int dmg = 20 + agility + (bleedBonus / 2);
            target.TakeDamage(dmg, 20);
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You enter Evade Stance, striking for " << dmg << " damage!\n";
        }
        else // Long: Detonate Stance (2 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Detonate Stance is on cooldown!", ConsoleHelper::Yellow); return; }
            int burnBonus = target.GetBurnMeter();
            int dmg = 30 + intellect + (burnBonus / 2);
            target.TakeDamage(dmg, 30);
            activeWeapon->TriggerLongSkill(2);
            std::cout << " > You enter Detonate Stance, detonating Burn buildup for " << dmg << " damage!\n";
        }
    }

    // FLAIL & SHIELD [STR / FOC]
    else if (wName == "Flail & Shield" || wName == "Flail and Shield" || wName == "Flail &amp; Shield")
    {
        if (!isLongSkill) // Short: Blessed Aegis (2 Turns)
        {
            if (!activeWeapon->CanUseShortSkill()) { ConsoleHelper::print("\n[!] Blessed Aegis is on cooldown!", ConsoleHelper::Yellow); return; }
            activeWeapon->TriggerShortSkill(2);
            std::cout << " > You raise Blessed Aegis!\n";
        }
        else // Long: Divine Smite (4 Turns)
        {
            if (!activeWeapon->CanUseLongSkill()) { ConsoleHelper::print("\n[!] Divine Smite is on cooldown!", ConsoleHelper::Yellow); return; }
            int dmg = 70 + strength + focus;
            target.TakeDamage(dmg, 60);
            activeWeapon->TriggerLongSkill(4);
            std::cout << " > You unleash Divine Smite for " << dmg << " damage!\n";
        }
    }
    else
    {
        ConsoleHelper::print("\n[!] This weapon has no special skills defined yet.", ConsoleHelper::Yellow);
    }
}
