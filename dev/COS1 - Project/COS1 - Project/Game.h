#pragma once
#include "Player.h"
#include "Enemy.h"
#include "GameUI.h"
#include "GameDifficulty.h"

class Game
{
private:
    Player* player;
    Enemy* currentBoss;
    GameDifficulty currentDifficulty;
    bool isRunning;

    // --- PRIVATE HELPER METHODS ---
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
    // --- CONSTRUCTORS & DESTRUCTOR ---
    Game();
    ~Game();

    // --- GAMEPLAY LIFECYCLE ---
    void Initialize();
    void DisplayWelcomeMenu();
    GameDifficulty SelectDifficulty();
    void DisplayMenu() const;
    void RunCombatLoop();
};
//Organized and Refactored