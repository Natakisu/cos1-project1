#include "Enemy.h"
#include "Player.h"
#include "Game.h" 
#include "ConsoleHelper.h"
#include <cstdlib> 
#include <iostream>

Enemy::Enemy(std::string name, int hp, int posture, GameDifficulty difficulty)
    : name(name), maxHP(hp), currentHP(hp), isStaggered(false),
    bleedMeter(0), burnMeter(0), frostbiteMeter(0),
    currentIntent(BossIntent::LightSweep)
{
    if (difficulty == GameDifficulty::Easy) {
        maxPosture = posture; // 50
        maxBleedThreshold = 100;
        maxBurnThreshold = 100;
    }
    else if (difficulty == GameDifficulty::Normal) {
        maxPosture = static_cast<int>(posture * 1.5); // 75
        maxBleedThreshold = 120;
        maxBurnThreshold = 120;
    }
    else if (difficulty == GameDifficulty::Hard) {
        maxPosture = posture * 2; // 100
        maxBleedThreshold = 150;
        maxBurnThreshold = 150;
    }
    else if (difficulty == GameDifficulty::Insane) {
        maxPosture = posture * 3; // 150
        maxBleedThreshold = 200;
        maxBurnThreshold = 200;
    }
    else if (difficulty == GameDifficulty::Impossible) {
        maxPosture = posture * 5; // 250
        maxBleedThreshold = 300;
        maxBurnThreshold = 300;
    }

    currentPosture = maxPosture;
}

void Enemy::GenerateIntent()
{
    int roll = rand() % 3;

    switch (roll)
    {
    case 0:
        currentIntent = BossIntent::LightSweep;
        break;
    case 1:
        currentIntent = BossIntent::HeavyCleave;
        break;
    case 2:
        currentIntent = BossIntent::DefensiveGuard;
        break;
    default:
        currentIntent = BossIntent::LightSweep;
        break;
    }
}

std::string Enemy::GetIntentDescription() const
{
    switch (currentIntent)
    {
    case BossIntent::HeavyCleave: return "Preparing a heavy attack!";
    case BossIntent::LightSweep: return "Preparing a quick sweep!";
    case BossIntent::DefensiveGuard: return "Raising guard!";
    default: return "Unknown intent";
    }
}

void Enemy::ExecuteIntent(Player& player)
{
    int damage = 0;

    if (currentIntent == BossIntent::LightSweep)
    {
        damage = 30;
        ConsoleHelper::print(" > " + name + " uses [Light Sweep] for " + std::to_string(damage) + " damage!", ConsoleHelper::Cyan);
    }
    else if (currentIntent == BossIntent::HeavyCleave)
    {
        damage = 55;
        ConsoleHelper::print(" > " + name + " unleashes [Heavy Cleave] for " + std::to_string(damage) + " damage!", ConsoleHelper::Cyan);
    }
    else if (currentIntent == BossIntent::DefensiveGuard)
    {
        ConsoleHelper::print(" > " + name + " takes a [Defensive Guard] stance, bolstering its posture!", ConsoleHelper::Yellow);
        damage = 0;
    }

    if (damage > 0)
    {
        player.TakeDamage(damage);
    }
}

void Enemy::TakeDamage(int damage, int postureDmg)
{
    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;

    currentPosture -= postureDmg;
    CheckPostureBreak();
}

void Enemy::ApplyStatusBuildup(int bleed, int burn, int frostbite)
{
    bleedMeter += bleed;
    burnMeter += burn;
    frostbiteMeter += frostbite;
}

void Enemy::CheckPostureBreak()
{
    if (currentPosture <= 0)
    {
        isStaggered = true;
        currentPosture = 0;
    }
}

void Enemy::ResetTurnState()
{
    if (isStaggered)
    {
        isStaggered = false;
        currentPosture = maxPosture;
    }
}

void Enemy::ResolveStatusEffects()
{
    // Bleed Check 
    if (bleedMeter >= maxBleedThreshold)
    {
        int bleedDmg = 75;
        currentHP -= bleedDmg;
        if (currentHP < 0) currentHP = 0;

        ConsoleHelper::print(" [!] BLOOD LOSS! " + name + " suffers " + std::to_string(bleedDmg) + " Hemorrhage damage!", ConsoleHelper::Red);
        bleedMeter = 0; // Reset meter after triggering
    }

    // Burn Check 
    if (burnMeter >= maxBurnThreshold)
    {
        int burnDmg = 40;
        currentHP -= burnDmg;
        if (currentHP < 0) currentHP = 0;

        ConsoleHelper::print(" [!] BLAZING! " + name + " burns for " + std::to_string(burnDmg) + " Fire damage!", ConsoleHelper::Yellow);
        burnMeter = 0; // Reset meter after triggering
    }
}