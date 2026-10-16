#pragma once
#include <string>

enum class BossIntent {
    LightSweep,
    HeavyCleave,
    DefensiveGuard
};

enum class GameDifficulty;

class Player;

class Enemy {
private:
    std::string name;
    int maxHP;
    int currentHP;
    int maxPosture;
    int currentPosture;
    bool isStaggered;

    int bleedMeter;
    int burnMeter;
    int frostbiteMeter;

    int maxBleedThreshold;
    int maxBurnThreshold;

    BossIntent currentIntent;

public:
    Enemy(std::string name, int hp, int posture, GameDifficulty difficulty);

    void GenerateIntent();
    std::string GetIntentDescription() const;
    void ExecuteIntent(Player& player);

    void TakeDamage(int damage, int postureDmg);
    void ApplyStatusBuildup(int bleed, int burn, int frostbite);
    void CheckPostureBreak();
    void ResetTurnState();
    void ResolveStatusEffects();

    // Getters
    int GetBleedMeter() const { return bleedMeter; }
    int GetBurnMeter() const { return burnMeter; }
    std::string GetName() const { return name; }
    int GetCurrentHP() const { return currentHP; }
    int GetCurrentPosture() const { return currentPosture; }
    bool IsAlive() const { return currentHP > 0; }
    int GetMaxHP() const { return maxHP; }
    int GetMaxPosture() const { return maxPosture; }
    int GetMaxBleedThreshold() const { return maxBleedThreshold; }
    int GetMaxBurnThreshold() const { return maxBurnThreshold; }
};