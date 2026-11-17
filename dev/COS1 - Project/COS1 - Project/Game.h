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
    void HandlePlayerAction(int choice);

    void StartFreshGameSession();
    void LoadExistingGameSession();

public:
    // --- CONSTRUCTORS & DESTRUCTOR ---
    Game();
    ~Game();

    // --- GAMEPLAY LIFECYCLE ---
    void Initialize();
    void DisplayWelcomeMenu();
    void SetupBossDifficulty();
    void RunCombatLoop();

    // Allow GameProgression to access session state if needed
    friend class GameProgression;
};
