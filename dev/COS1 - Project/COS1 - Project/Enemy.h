#pragma once
#include <string>

enum class BossIntent 
{
    HeavyCleave,
    LightSweep,
    DefensiveGuard,
    ChargingUp
};

class Enemy 
{
private:
    std::string name;
    int maxHP, currentHP;
    int maxPosture, currentPosture;
    bool isStaggered;

    // Status Meter Buildups
    int bleedMeter;
    int burnMeter;
    int frostbiteMeter;

    // Telegraphed Intent
    BossIntent currentIntent;

public:
    Enemy(std::string name, int hp, int posture);

    // Intent System
    void GenerateIntent();
    BossIntent GetCurrentIntent() const { return currentIntent; }
    std::string GetIntentDescription() const;
    void ExecuteIntent(class Player& player);

    // Combat & Posture
    void TakeDamage(int damage, int postureDmg);
    void ApplyStatusBuildup(int bleed, int burn, int frostbite);
    void CheckPostureBreak();
    void ResetTurnState();

    // Getters
    std::string GetName() const { return name; }
    int GetCurrentHP() const { return currentHP; }
    int GetCurrentPosture() const { return currentPosture; }
    bool IsStaggered() const { return isStaggered; }
    bool IsAlive() const { return currentHP > 0; }
};