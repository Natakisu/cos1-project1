#pragma once
#include "Player.h"
#include "Enemy.h"

class GameProgression
{
public:
    // Handles XP and Relic Shard rewards upon defeating a boss
    static void HandleVictoryRewards(Player* player, GameDifficulty difficulty);

    // Displays the victory menu options
    // Returns false if the game should exit or return to main menu
    static bool HandleVictoryMenu(Player* player, Game& gameRef, bool& isRunning);

    // Displays the death/game over screen and handles reloading saves or resetting
    static void HandleDeathMenu(Player* player, Game& gameRef);

    // Renders combat outcome banners (Victory vs. Defeat)
    static void DisplayCombatOutcome(bool isPlayerAlive);
};