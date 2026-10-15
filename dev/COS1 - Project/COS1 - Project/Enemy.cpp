#include "Enemy.h"
#include "Player.h"
#include <cstdlib> 
#include <iostream>

Enemy::Enemy(std::string name, int hp, int posture)
    : name(name), maxHP(hp), currentHP(hp), maxPosture(posture), currentPosture(posture),
    isStaggered(false), bleedMeter(0), burnMeter(0), frostbiteMeter(0),
    currentIntent(BossIntent::LightSweep) {
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
        std::cout << " > " << name << " uses [Light Sweep] for " << damage << " damage!\n";
    }
    else if (currentIntent == BossIntent::HeavyCleave)
    {
        damage = 55; // Or your calculated damage value
        std::cout << " > " << name << " unleashes [Heavy Cleave] for " << damage << " damage!\n";
    }
    else if (currentIntent == BossIntent::DefensiveGuard)
    {
        std::cout << " > " << name << " takes a [Defensive Guard] stance, bolstering its posture!\n";
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