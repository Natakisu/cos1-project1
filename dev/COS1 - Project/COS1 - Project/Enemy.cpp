#include "Enemy.h"
#include "Player.h"
#include "Game.h" 
#include "ConsoleHelper.h"
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <climits>

// --- CONSTRUCTORS & INITIALIZATION ---
Enemy::Enemy(std::string name, int hp, int posture, GameDifficulty difficulty)
    : name(name), maxHP(hp), currentHP(hp), isStaggered(false),
    bleedMeter(0), burnMeter(0), frostbiteMeter(0),
    currentIntent(BossIntent::LightSweep)
{
    if (difficulty == GameDifficulty::Easy) {
        maxPosture = posture;
        maxBleedThreshold = 100;
        maxBurnThreshold = 100;
        maxFrostbiteThreshold = 100;
    }
    else if (difficulty == GameDifficulty::Normal) {
        maxPosture = static_cast<int>(posture * 1.5);
        maxBleedThreshold = 120;
        maxBurnThreshold = 120;
        maxFrostbiteThreshold = 120;
    }
    else if (difficulty == GameDifficulty::Hard) {
        maxPosture = posture * 2;
        maxBleedThreshold = 150;
        maxBurnThreshold = 150;
        maxFrostbiteThreshold = 150;
    }
    else if (difficulty == GameDifficulty::Insane) {
        maxPosture = posture * 3;
        maxBleedThreshold = 200;
        maxBurnThreshold = 200;
        maxFrostbiteThreshold = 200;
    }
    else if (difficulty == GameDifficulty::Impossible) {
        maxPosture = posture * 5;
        maxBleedThreshold = 300;
        maxBurnThreshold = 300;
        maxFrostbiteThreshold = 300;
    }

    currentPosture = maxPosture;
}

// --- INTENT & COMBAT AI ---
void Enemy::GenerateIntent()
{
    int roll = rand() % 3;

    switch (roll)
    {
    case 0: currentIntent = BossIntent::LightSweep; break;
    case 1: currentIntent = BossIntent::HeavyCleave; break;
    case 2: currentIntent = BossIntent::DefensiveGuard; break;
    default: currentIntent = BossIntent::LightSweep; break;
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

// --- DAMAGE & STATUS HANDLERS ---
void Enemy::TakeDamage(int damage, int postureDamage)
{
    // Prevent negative damage from wrapping or healing the enemy unexpectedly
    if (damage < 0) damage = 0;

    // Strict boundary checks against integer overflow and underflow
    if (damage >= currentHP)
    {
        currentHP = 0;
    }
    else
    {
        currentHP -= damage;
    }

    // Apply posture damage clamp as well
    currentPosture = std::max(0, currentPosture - postureDamage);
}

void Enemy::ApplyStatusBuildup(int bleed, int burn, int frostbite)
{
    bleedMeter = std::max(0, bleedMeter + bleed);
    burnMeter = std::max(0, burnMeter + burn);
    frostbiteMeter = std::max(0, frostbiteMeter + frostbite);
}

void Enemy::CheckPostureBreak()
{
    if (currentPosture <= 0)
    {
        isStaggered = true;
        currentPosture = 0;
    }
}

void Enemy::ResolveStatusEffects()
{
    // Bleed Check 
    if (bleedMeter >= maxBleedThreshold)
    {
        int bleedDmg = 75;
        currentHP = std::max(0, currentHP - bleedDmg);

        ConsoleHelper::print(" [!] BLOOD LOSS! " + name + " suffers " + std::to_string(bleedDmg) + " Hemorrhage damage!", ConsoleHelper::Red);
        bleedMeter = 0;
    }

    // Burn Check 
    if (burnMeter >= maxBurnThreshold)
    {
        int burnDmg = 40;
        currentHP = std::max(0, currentHP - burnDmg);

        ConsoleHelper::print(" [!] BLAZING! " + name + " burns for " + std::to_string(burnDmg) + " Fire damage!", ConsoleHelper::Yellow);
        burnMeter = 0;
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