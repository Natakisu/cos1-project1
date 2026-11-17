#pragma once
#include "Player.h"
#include "Enemy.h"
#include "GameUI.h"

class Game
{
private:
    Player* player;
    Enemy* currentBoss;
    GameDifficulty currentDifficulty;
    bool isRunning;

    // Private Helper Methods (Declared only once)
    bool HandleInventoryMenu();
    bool HandleWeaponSkillMenu();
    void HandleVictoryRewards();
    bool HandleVictoryMenu();
    void HandleDeathMenu();
    void HandlePlayerAction(int choice);
    void HandleCombatOutcome() const;

    void StartFreshGameSession();
    void LoadExistingGameSession();
    void SetupBossDifficulty();

public:
    Game();
    ~Game();

    void Initialize();
    void DisplayWelcomeMenu();
    GameDifficulty SelectDifficulty();
    void DisplayMenu() const;
    void RunCombatLoop();
};