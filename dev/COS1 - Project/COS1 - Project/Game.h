#pragma once
#include "Player.h"
#include "Enemy.h"

class Game 
{
private:
    void RenderHUD() const;
    void DisplayActionMenu() const;
    int GetValidatedPlayerChoice() const;
    void ProcessPlayerTurn(int choice);
    void ProcessEnemyTurn();

public:
    void RunCombatLoop();
};