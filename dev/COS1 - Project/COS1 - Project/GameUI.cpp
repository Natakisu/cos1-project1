#include "GameUI.h"
#include "ConsoleHelper.h"
#include "GameInput.h"
#include <iostream>
#include <cstdlib>

void GameUI::DisplayWelcomeMenu()
{
    system("cls");
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("               [ RELIC SWITCHER ]                 ", ConsoleHelper::Cyan);
    ConsoleHelper::print("          A C++ Console RPG Experience            ", ConsoleHelper::White);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print(" 1. Start New Game                                ", ConsoleHelper::White);
    ConsoleHelper::print(" 2. View Instructions                             ", ConsoleHelper::White);
    ConsoleHelper::print(" 3. Exit Game                                     ", ConsoleHelper::White);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
}

void GameUI::DisplayInstructions()
{
    system("cls");
    ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
    ConsoleHelper::print("                  GAME INSTRUCTIONS                ", ConsoleHelper::Cyan);
    ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
    ConsoleHelper::print(" - Relic Switcher is a Turn-Based RPG with elements", ConsoleHelper::White);
    ConsoleHelper::print("    from New World Aeternum and Dark Souls         ", ConsoleHelper::White);
    ConsoleHelper::print(" - Allocate attributes wisely during creation.     ", ConsoleHelper::White);
    ConsoleHelper::print(" - Choose a Primary and Secondary weapon loadout.  ", ConsoleHelper::White);
    ConsoleHelper::print(" - Choose a Difficulty you would like to play.     ", ConsoleHelper::White);
    ConsoleHelper::print(" - Fight the Relic Guardian using Attacks, Blocks, ", ConsoleHelper::White);
    ConsoleHelper::print("    and Dodges while managing your HP, SP, and MP. ", ConsoleHelper::White);
    ConsoleHelper::print("---------------------------------------------------", ConsoleHelper::Cyan);
}

void GameUI::DisplayCombatMenu()
{
    ConsoleHelper::print("1. Light Attack", ConsoleHelper::White);
    ConsoleHelper::print("2. Heavy Attack", ConsoleHelper::White);
    ConsoleHelper::print("3. Swap Weapon", ConsoleHelper::White);
    ConsoleHelper::print("4. Block", ConsoleHelper::White);
    ConsoleHelper::print("5. Dodge", ConsoleHelper::White);
    ConsoleHelper::print("6. Inspect Weapons", ConsoleHelper::White);
    ConsoleHelper::print("9. [DEBUG] Instant Win / Kill Boss", ConsoleHelper::Yellow);
}

void GameUI::DisplayAttributeDescriptions()
{
    system("cls");
    ConsoleHelper::print("--- Attribute Descriptions ---", ConsoleHelper::Cyan);
    ConsoleHelper::print(" - Constitution (CON): Increases your Max HP.", ConsoleHelper::White);
    ConsoleHelper::print(" - Strength     (STR): Increases physical weapon damage.", ConsoleHelper::White);
    ConsoleHelper::print(" - Agility      (AGI): Increases Stamina (SP) and dodging/speed.", ConsoleHelper::White);
    ConsoleHelper::print(" - Intellect    (INT): Increases Mana (MP) and magical effectiveness.", ConsoleHelper::White);
    ConsoleHelper::print(" - Focus        (FOC): Increases your healing potency and recovery.", ConsoleHelper::White);
}

void GameUI::RenderCombatUI(const Player* player, const Enemy* currentBoss)
{
    if (!player || !currentBoss) return;

    auto drawBar = [](int current, int max, int totalBlocks = 10) {
        if (max <= 0) max = 1;
        if (current < 0) current = 0;

        // Prevent out-of-bounds ratios 
        double ratio = static_cast<double>(current) / static_cast<double>(max);
        if (ratio > 1.0) ratio = 1.0;
        if (ratio < 0.0) ratio = 0.0;

        int filledCount = static_cast<int>(ratio * totalBlocks);

        std::cout << "[";
        for (int i = 0; i < totalBlocks; ++i) {
            if (i < filledCount) {
                ConsoleHelper::print("#", ConsoleHelper::Green, false);
            }
            else {
                ConsoleHelper::print("-", ConsoleHelper::Red, false);
            }
        }
        std::cout << "] " << current << "/" << max;
        };

    ConsoleHelper::print("\n==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print(" PLAYER: " + player->GetName(), ConsoleHelper::White);
    std::cout << " HP: "; drawBar(player->GetCurrentHP(), player->GetMaxHP()); std::cout << "\n";
    std::cout << " SP: "; drawBar(player->GetCurrentSP(), player->GetMaxSP()); std::cout << "\n";
    std::cout << " MP: "; drawBar(player->GetCurrentMP(), player->GetMaxMP()); std::cout << "\n";
    std::cout << " XP: "; drawBar(player->GetCurrentXP(), player->GetXPToNextLevel());
    std::cout << " (Lvl: " << player->GetLevel() << ")\n";

    ConsoleHelper::print("--------------------------------------------------", ConsoleHelper::Cyan);
    ConsoleHelper::print(" BOSS:   " + currentBoss->GetName(), ConsoleHelper::White);
    std::cout << " HP:      "; drawBar(currentBoss->GetCurrentHP(), currentBoss->GetMaxHP()); std::cout << "\n";
    std::cout << " Posture: "; drawBar(currentBoss->GetCurrentPosture(), currentBoss->GetMaxPosture()); std::cout << "\n";
    std::cout << " Bleed:   "; drawBar(currentBoss->GetBleedMeter(), 100); std::cout << "\n";
    std::cout << " Burn:    "; drawBar(currentBoss->GetBurnMeter(), 100); std::cout << "\n";

    ConsoleHelper::print(" BOSS INTENT: ", ConsoleHelper::White, false);
    ConsoleHelper::print(currentBoss->GetIntentDescription(), ConsoleHelper::Yellow);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
}

GameDifficulty GameUI::SelectDifficulty()
{
    system("cls");
    ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("                    [ SELECT GAME DIFFICULTY ]                    |", ConsoleHelper::Cyan);
    ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print(" 1. Easy       (Boss HP: 500     | Barely A Challenge  | XP:  150)|", ConsoleHelper::Green);
    ConsoleHelper::print(" 2. Normal     (Boss HP: 5000    | Standard Experience | XP:  300)|", ConsoleHelper::Cyan);
    ConsoleHelper::print(" 3. Hard       (Boss HP: 50000   | Harder Experience   | XP:  600)|", ConsoleHelper::White);
    ConsoleHelper::print(" 4. Insane     (Boss HP: 500000  | Soulslike Challenge | XP: 1200)|", ConsoleHelper::Yellow);
    ConsoleHelper::print(" 5. Impossible (Boss HP: 5000000 | Why? Why Do This?   | XP: 2400)|", ConsoleHelper::Red);
    ConsoleHelper::print("===================================================================", ConsoleHelper::Cyan);

    int choice = GameInput::GetValidatedChoice(1, 5);
    return static_cast<GameDifficulty>(choice - 1);
}