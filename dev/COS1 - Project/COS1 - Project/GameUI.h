#pragma once
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "GameDifficulty.h"

class GameUI
{
public:
    // --- WELCOME & INSTRUCTION SCREENS ---
    static void DisplayWelcomeMenu();
    static void DisplayInstructions();

    // --- CHARACTER CREATION & ATTRIBUTES ---
    static void DisplayAttributeDescriptions();
    static GameDifficulty SelectDifficulty();

    // --- COMBAT HUD & MENUS ---
    static void DisplayCombatMenu();
    static void RenderCombatUI(const Player* player, const Enemy* currentBoss);
};
//Organized and Refactored