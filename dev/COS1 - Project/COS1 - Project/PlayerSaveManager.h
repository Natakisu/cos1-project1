#pragma once
#include <string>

class Player;

class PlayerSaveManager
{
public:
    static void Save(const Player* player, const std::string& filename);
    static void Load(Player* player, const std::string& filename);
};