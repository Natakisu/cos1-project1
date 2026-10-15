#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
private:
    Player* player;
    Enemy* currentBoss;
    bool isRunning;

    // Vector and Helper Methods for weapon selection
    std::vector<Weapon*> availableWeapons;

    void InitializeWeaponPool();
    void WeaponSelectionMenu();

    // Helper Methods (Cleaned up duplicates and typos)
    int GetValidatedPlayerChoice();
    void ProcessPlayerTurn(int choice);
    void ProcessEnemyTurn();

public:
    Game();
    ~Game();

    void Initialize();
    void CharacterCreation();
    void RunCombatLoop();

    // Public action and outcome handlers used by the loop
    void HandlePlayerAction(int choice);
    void HandleCombatOutcome() const;

    // UI rendering helpers
    void RenderUI() const;
    void DisplayMenu() const;

    bool IsRunning() const
    {
        return isRunning;
    }
};