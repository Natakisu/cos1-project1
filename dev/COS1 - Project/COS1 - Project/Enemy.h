#pragma once
#include <string>
#include "GameDifficulty.h"

class Player;

// --- ENEMY AI INTENTS ---
enum class BossIntent
{
    LightSweep,
    HeavyCleave,
    DefensiveGuard
};

class Enemy
{
private:
    // Core Stats & Posture
    std::string name;
    int maxHP, currentHP;
    int maxPosture, currentPosture;
    bool isStaggered;

    // Status Buildup & Thresholds
    int bleedMeter, burnMeter, frostbiteMeter;
    int maxBleedThreshold, maxBurnThreshold, maxFrostbiteThreshold;

    BossIntent currentIntent;

public:
    // --- CONSTRUCTORS ---
    Enemy(std::string name, int hp, int posture, GameDifficulty difficulty);

    // --- COMBAT AI & INTENTS ---
    void GenerateIntent();
    std::string GetIntentDescription() const;
    void ExecuteIntent(Player& player);

    // --- DAMAGE & STATUS HANDLERS ---
    void TakeDamage(int damage, int postureDmg);
    void ApplyStatusBuildup(int bleed, int burn, int frostbite);
    void CheckPostureBreak();
    void ResolveStatusEffects();
    void ResetTurnState();

    // --- GETTERS ---
    std::string GetName() const { return name; }
    bool IsAlive() const { return currentHP > 0; }

    int GetCurrentHP() const { return currentHP; }
    int GetMaxHP() const { return maxHP; }
    int GetCurrentPosture() const { return currentPosture; }
    int GetMaxPosture() const { return maxPosture; }

    int GetBleedMeter() const { return bleedMeter; }
    int GetBurnMeter() const { return burnMeter; }
    int GetFrostbiteMeter() const { return frostbiteMeter; }

    int GetMaxBleedThreshold() const { return maxBleedThreshold; }
    int GetMaxBurnThreshold() const { return maxBurnThreshold; }
    int GetMaxFrostbiteThreshold() const { return maxFrostbiteThreshold; }
};
//Organized and Refactored