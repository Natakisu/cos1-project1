#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "ConsoleHelper.h"

Player::Player(std::string name)
    : name(name),
    constitution(10), strength(10), agility(10), intellect(10), focus(10),
    maxHP(100), currentHP(100), maxSP(100), currentSP(100), maxMP(100), currentMP(100),
    primaryWeapon(nullptr), secondaryWeapon(nullptr), isPrimaryActive(true),
    isBlocking(false), isDodging(false)
{
    RecalculatePools();
    currentHP = maxHP;
    currentSP = maxSP;
    currentMP = maxMP;
}

Player::~Player()
{
    // Memory Cleanup Addressed
    delete primaryWeapon;
    delete secondaryWeapon;
    primaryWeapon = nullptr;
    secondaryWeapon = nullptr;
}

void Player::AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints) {
    constitution += conPoints;
    strength += strPoints;
    agility += agiPoints;
    intellect += intPoints;
    focus += focPoints;
    RecalculatePools();
}

void Player::RecalculatePools()
{
    maxHP = constitution * 10;
    maxSP = agility * 10;
    maxMP = intellect * 10;
}

void Player::EquipWeapons(Weapon* primary, Weapon* secondary)
{
    primaryWeapon = primary;
    secondaryWeapon = secondary;
}

bool Player::SwapWeapon()
{
    if (currentSP < 10) return false; // Stamina cost for swapping

    isPrimaryActive = !isPrimaryActive;
    currentSP -= 10;
    return true;
}

int Player::PerformLightAttack(Enemy& target)
{
    Weapon* activeWeapon = GetActiveWeapon();
    if (!activeWeapon) {
        return 0;
    }

    std::string weaponName = activeWeapon->GetName();

    // 1. Life Staff Heals the player instead of dealing damage
    if (weaponName == "Life Staff")
    {
        int healingAmount = 25 + (focus * 2);
        currentHP += healingAmount;
        if (currentHP > GetMaxHP()) currentHP = GetMaxHP();

        ConsoleHelper::print(" > " + name + " channels the Life Staff, restoring " + std::to_string(healingAmount) + " HP!", ConsoleHelper::Green);
        return 0; // Skips dealing damage to the boss
    }

    // Check stamina cost for standard weapons
    if (currentSP < activeWeapon->GetAttackStaminaCost()) {
        ConsoleHelper::print("[!] Not enough stamina for light attack!", ConsoleHelper::Red);
        return 0;
    }

    currentSP -= activeWeapon->GetAttackStaminaCost();
    int damage = activeWeapon->CalculateDamage(strength, agility, intellect, focus);

    target.TakeDamage(damage, activeWeapon->GetPostureDamage());

    // 2. Flail and Shield heal on attack if Focus >= 12
    if (weaponName == "Flail and Shield")
    {
        if (focus >= 12)
        {
            int drainHeal = 10 + focus;
            currentHP += drainHeal;
            if (currentHP > GetMaxHP()) currentHP = GetMaxHP();
            ConsoleHelper::print(" [+] Flail & Shield life-drain active! Restored " + std::to_string(drainHeal) + " HP.", ConsoleHelper::Green);
        }
        else
        {
            ConsoleHelper::print(" [-] Focus too low (<12 FOC) to trigger Flail life-drain!", ConsoleHelper::Red);
        }
    }

    return damage;
}

int Player::PerformHeavyAttack(Enemy& target) {
    Weapon* activeWeapon = GetActiveWeapon();
    if (!activeWeapon) return 0;

    std::string weaponName = activeWeapon->GetName();

    // Life Staff doesn't do heavy physical attacks, but a stronger heal
    if (weaponName == "Life Staff")
    {
        int healingAmount = 50 + (focus * 4);
        currentHP += healingAmount;
        if (currentHP > GetMaxHP()) currentHP = GetMaxHP();

        ConsoleHelper::print(" > " + name + " heavily channels the Life Staff, restoring " + std::to_string(healingAmount) + " HP!", ConsoleHelper::Green);
        return 0;
    }

    int staminaCost = activeWeapon->GetAttackStaminaCost() * 2;
    if (currentSP < staminaCost) {
        ConsoleHelper::print("[!] Not enough stamina for heavy attack!", ConsoleHelper::Red);
        return 0;
    }

    currentSP -= staminaCost;

    int damage = (activeWeapon->CalculateDamage(strength, agility, intellect, focus) * 3) / 2;

    target.TakeDamage(damage, activeWeapon->GetPostureDamage() * 2);

    // Flail and shield heavy attack drain check
    if (weaponName == "Flail and Shield")
    {
        if (focus >= 12)
        {
            int drainHeal = 20 + (focus * 2);
            currentHP += drainHeal;
            if (currentHP > GetMaxHP()) currentHP = GetMaxHP();
            ConsoleHelper::print(" [+] Heavy Flail & Shield life-drain active! Restored " + std::to_string(drainHeal) + " HP.", ConsoleHelper::Green);
        }
        else
        {
            ConsoleHelper::print(" [-] Focus too low (<12 FOC) to trigger Heavy Flail life-drain!", ConsoleHelper::Red);
        }
    }

    return damage;
}

void Player::Block()
{
    isBlocking = true;
}

void Player::Dodge()
{
    isDodging = true;
}

void Player::RegainResourcesPerTurn()
{
    currentSP = std::min(maxSP, currentSP + 20);
    currentMP = std::min(maxMP, currentMP + 10);
    isBlocking = false;
    isDodging = false;
}

void Player::TakeDamage(int damage)
{
    if (isDodging) return; // Negate damage on dodge

    if (isBlocking)
    {
        damage /= 2; // Reduce damage when blocking
    }

    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;
}

void Player::SetAttributes(int con, int str, int agi, int intel, int foc) {
    constitution = con;
    strength = str;
    agility = agi;
    intellect = intel;
    focus = foc;
    RecalculatePools();
    currentHP = maxHP;
    currentSP = maxSP;
    currentMP = maxMP;
}

void Player::DisplayStats() const {
    system("cls"); // Clear the main menu away

    ConsoleHelper::print("--- " + name + "'s Attributes ---", ConsoleHelper::Cyan);
    std::cout << "Constitution (CON): " << constitution << " (Max HP: " << maxHP << ")\n";
    std::cout << "Strength     (STR): " << strength << "\n";
    std::cout << "Agility      (AGI): " << agility << " (Max SP: " << maxSP << ")\n";
    std::cout << "Intellect    (INT): " << intellect << " (Max MP: " << maxMP << ")\n";
    std::cout << "Focus        (FOC): " << focus << "\n";
    ConsoleHelper::print("---------------------------\n", ConsoleHelper::Cyan);

    // Pause so the player can read their stats before returning to the main menu
    ConsoleHelper::print("Press Enter to return to the main menu...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}

void Player::InspectWeapons() const {
    system("cls"); // Clear previous screen

    ConsoleHelper::print("=== EQUIPPED WEAPONS ===", ConsoleHelper::Cyan);
    if (isPrimaryActive) ConsoleHelper::print("[ACTIVE] ", ConsoleHelper::Green, false);
    else std::cout << "[STOWED] ";
    if (primaryWeapon) primaryWeapon->DisplayWeaponInfo();

    std::cout << "\n";
    if (!isPrimaryActive) ConsoleHelper::print("[ACTIVE] ", ConsoleHelper::Green, false);
    else std::cout << "[STOWED] ";
    if (secondaryWeapon) secondaryWeapon->DisplayWeaponInfo();
    ConsoleHelper::print("========================", ConsoleHelper::Cyan);

    // Pause so they can look over both weapons
    ConsoleHelper::print("\nPress Enter to return to the main menu...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}

void Player::GainXP(int amount)
{
    currentXP += amount;
    int xpNeeded = 1000; // Adjust base threshold as needed

    while (currentXP >= xpNeeded)
    {
        currentXP -= xpNeeded; // <--- Prevents the infinite loop!
        level++;

        std::cout << "\n[!] LEVEL UP! You reached Level " << level << "!\n";

        // Scale requirement for next level using standard integer multiplication
        xpNeeded = (xpNeeded * 3) / 2; // Increases by 50% cleanly without casts
    }
}

void Player::LevelUp()
{
    level++;
    xpToNextLevel = (int)(xpToNextLevel * 1.5f); // Scale requirement
    unspentAttributePoints += 5; // +5 points per level

    ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("          [ LEVEL UP! ]                 ", ConsoleHelper::Green);
    ConsoleHelper::print(" You reached Level " + std::to_string(level) + "!", ConsoleHelper::White);
    ConsoleHelper::print(" You gained 5 unspent attribute points!", ConsoleHelper::Yellow);
    ConsoleHelper::print("========================================", ConsoleHelper::Cyan);
}

void Player::AllocateAttribute(int choice, int amount)
{
    if (amount > unspentAttributePoints) amount = unspentAttributePoints;
    if (amount <= 0) return;

    if (choice == 1) constitution += amount;
    else if (choice == 2) strength += amount;
    else if (choice == 3) agility += amount;
    else if (choice == 4) intellect += amount;
    else if (choice == 5) focus += amount;

    unspentAttributePoints -= amount;
    UpdateDerivedStats(); 
}

void Player::SaveToFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (outFile.is_open())
    {
        // Core info
        outFile << name << "\n";
        outFile << level << "\n";
        outFile << currentXP << "\n";
        outFile << maxHP << "\n";
        outFile << currentHP << "\n";

        // Attributes & Points
        outFile << constitution << "\n";
        outFile << strength << "\n";
        outFile << agility << "\n";
        outFile << intellect << "\n";
        outFile << focus << "\n";
        outFile << unspentAttributePoints << "\n";

        outFile.close();
        ConsoleHelper::print("[!] Game saved successfully!", ConsoleHelper::Green);
    }
    else
    {
        ConsoleHelper::print("[!] Error: Could not open file for saving.", ConsoleHelper::Red);
    }
}

void Player::LoadFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        // Core info
        std::getline(inFile, name);
        inFile >> level;
        inFile >> currentXP;
        inFile >> maxHP;
        inFile >> currentHP;

        // Attributes & Points
        inFile >> constitution;
        inFile >> strength;
        inFile >> agility;
        inFile >> intellect;
        inFile >> focus;
        inFile >> unspentAttributePoints;

        inFile.close();

        // Recalculate derived pools (maxHP, maxSP, maxMP) based on loaded attributes!
        UpdateDerivedStats();

        ConsoleHelper::print("[!] Game loaded successfully!", ConsoleHelper::Green);
    }
    else
    {
        ConsoleHelper::print("[!] Error: No save file found. Starting fresh.", ConsoleHelper::Yellow);
    }
}