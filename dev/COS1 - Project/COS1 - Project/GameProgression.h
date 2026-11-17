#pragma once
#include "Player.h"
#include "Enemy.h"
#include "GameDifficulty.h"

// Forward declaration to avoid circular header includes
class Game;

class GameProgression
{
public:
    static void HandleVictoryRewards(Player* player, GameDifficulty difficulty);
    static bool HandleVictoryMenu(Player* player, Game& gameRef, bool& isRunning);
    static void HandleDeathMenu(Player* player, Game& gameRef);
    static void DisplayCombatOutcome(bool isPlayerAlive);
};