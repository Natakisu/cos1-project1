#pragma once
#include "Player.h"

class CharacterManager
{
public:
    // Creates a new player, prompts for a name, and grants initial unspent points
    static Player* CreateCharacter();

    // Runs the attribute allocation loop inside the Prep Hub
    static void RunAttributeAllocationMenu(Player* player);
};