#pragma once
#include "Player.h"
#include "Game.h"

class PreparationMenu
{
public:
    // --- PREPARATION HUB LIFECYCLE ---
    static void Open(Player* player);

    // --- DEBUG & UTILITY MENUS ---
    static void OpenDebugMenu(Player* player);
};
//Organized and Refactored