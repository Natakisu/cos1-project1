#pragma once
#include <string>
#include "Player.h"
#include "Enemy.h"

// Forward declaration instead of #include "Game.h" to avoid circular dependencies
enum class GameDifficulty;

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