#pragma once
#include <string>
#include "Player.h"

class CharacterManager
{
public:
    // Handles interactive name entry, initializing the player, and allocating starting points
    static Player* CreateCharacter();

    // Runs the dedicated attribute allocation loop for existing players with unspent points
    static void RunAttributeAllocationMenu(Player* player);
};