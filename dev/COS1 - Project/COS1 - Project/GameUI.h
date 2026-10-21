#pragma once
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

class GameUI
{
public:
    static void DisplayWelcomeMenu();
    static void DisplayInstructions();
    static void DisplayCombatMenu();
    static void DisplayAttributeDescriptions();
    static void RenderCombatUI(const Player* player, const Enemy* currentBoss);
    static GameDifficulty SelectDifficulty();
};