#pragma once
#include "Player.h"
#include "Game.h"

class PreparationMenu
{
public:
    // Runs the pre-battle hub loop. Returns true when ready to proceed to difficulty selection.
    static void Open(Player* player);

    // Runs the dedicated attribute allocation loop for existing players with unspent points
    static void RunAttributeAllocationMenu(Player* player);

    static void OpenDebugMenu(Player* player); // DEBUG / Cheat Menu
};