#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

enum class GameDifficulty 
{
    Easy,
    Normal,
    Hard,
    Insane,
    Impossible
};

class Game
{
private:
    Player* player;
    Enemy* currentBoss;
    bool isRunning;

    GameDifficulty currentDifficulty;

    void LoadExistingGameSession();
    void StartFreshGameSession();
    void SetupBossDifficulty();

public:
    Game();
    ~Game();

    void DisplayWelcomeMenu();
    void Initialize();
    void CharacterCreation();
    void AllocateAttributesMenu();
    void RunCombatLoop();

    // Public action and outcome handlers used by the loop
    void HandlePlayerAction(int choice);
    void HandleCombatOutcome() const;

    // UI rendering helpers
    void DisplayMenu() const;

    bool IsRunning() const
    {
        return isRunning;
    }
    GameDifficulty SelectDifficulty();
};