#pragma once
#include "Player.h"
#include "Enemy.h"

class Game 
{
private:
    Player* player;
    Enemy* currentBoss;
    bool isRunning;

    // Helper Methods
    int GetValidatedPlayerChoice() const;
    void ProccessPlayerTurn(int choice);
    void ProccessEnemyTurn();

public:
    Game();
    ~Game();

    void Initialize();
    void CharacterCreation();
    void RunCombatLoop();

// UI rendering helpers
    void RenderUI() const;
    void DisplayMenu() const;

    bool IsRunning() const 
    {
        return isRunning;
    }
};