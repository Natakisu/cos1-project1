#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(std::string name, int hp, int posture)
    : name(name), maxHP(hp), currentHP(hp), maxPosture(posture), currentPosture(posture),
    isStaggered(false), bleedMeter(0), burnMeter(0), frostbiteMeter(0),
    currentIntent(BossIntent::LightSweep) {
}

void Enemy::GenerateIntent() 
{
    // Simple placeholder intent cycle logic
    currentIntent = BossIntent::HeavyCleave;
}

std::string Enemy::GetIntentDescription() const 
{
    switch (currentIntent) 
    {
    case BossIntent::HeavyCleave: return "Preparing a heavy attack!";
    case BossIntent::LightSweep: return "Preparing a quick sweep!";
    case BossIntent::DefensiveGuard: return "Raising guard!";
    case BossIntent::ChargingUp: return "Gathering energy!";
    default: return "Unknown intent";
    }
}

void Enemy::ExecuteIntent(Player& player) 
{
    if (isStaggered) return;

    switch (currentIntent) 
    {
    case BossIntent::HeavyCleave:
        player.TakeDamage(25);
        break;
    case BossIntent::LightSweep:
        player.TakeDamage(12);
        break;
    default:
        break;
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
        currentPosture = maxPosture; // Reset posture after stagger turn finishes
    }
}