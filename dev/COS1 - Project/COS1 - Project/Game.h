#pragma once
#include "Player.h"
#include "Enemy.h"

class Game 
{
private:
    Player* player;
    Enemy* currentBoss;
    bool isRunning;

public:
    Game();
    ~Game();

    void Initialize();
    void CharacterCreation();
    void RunCombatLoop();
    void RenderUI() const;
    void DisplayMenu() const;

    bool IsRunning() const { return isRunning; }
};