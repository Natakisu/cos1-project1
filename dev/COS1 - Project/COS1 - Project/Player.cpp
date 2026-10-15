#include <iostream>
#include "Player.h"
#include "Enemy.h"

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

        std::cout << " > " << name << " channels the Life Staff, restoring " << healingAmount << " HP!\n";
        return 0; // Skips dealing damage to the boss
    }

    // Check stamina cost for standard weapons
    if (currentSP < activeWeapon->GetAttackStaminaCost()) {
        std::cout << "[!] Not enough stamina for light attack!\n";
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
            std::cout << " > Flail & Shield life-drain actived! Restored " << drainHeal << " HP.\n";
        }
        else
        {
            std::cout << "[-] Focus too low (<12 FOC) to trigger Flail life-drain!\n";
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

        std::cout << " > " << name << " heavily channels the Life Staff, restoring " << healingAmount << " HP!\n";
        return 0;
    }

    int staminaCost = activeWeapon->GetAttackStaminaCost() * 2;
    if (currentSP < staminaCost) {
        std::cout << "[!] Not enough stamina for heavy attack!\n";
        return 0;
    }

    currentSP -= staminaCost;

    int damage = (activeWeapon->CalculateDamage(strength, agility, intellect, focus) * 3) / 2; 

    target.TakeDamage(damage, activeWeapon->GetPostureDamage() * 2);

    // Flail and shield heavy attack drain check
    if (weaponName == "Flail and Shield" && focus >= 2)
    {
        int drainHeal = 20 + (focus * 2);
        currentHP += drainHeal;
        if (currentHP > GetMaxHP()) currentHP = GetMaxHP();
        std::cout << " < Flail & Shield life-drain active! Restored " << drainHeal << " HP.\n";
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
    std::cout << "\n--- " << name << "'s Attributes ---\n";
    std::cout << "Constitution (CON): " << constitution << " (Max HP: " << maxHP << ")\n";
    std::cout << "Strength     (STR): " << strength << "\n";
    std::cout << "Agility      (AGI): " << agility << " (Max SP: " << maxSP << ")\n";
    std::cout << "Intellect    (INT): " << intellect << " (Max MP: " << maxMP << ")\n";
    std::cout << "Focus        (FOC): " << focus << "\n";
    std::cout << "---------------------------\n";
}

void Player::InspectWeapons() const {
    std::cout << "\n=== EQUIPPED WEAPONS ===\n";
    std::cout << (isPrimaryActive ? "[ACTIVE] " : "[STOWED] ");
    if (primaryWeapon) primaryWeapon->DisplayWeaponInfo();

    std::cout << "\n" << (!isPrimaryActive ? "[ACTIVE] " : "[STOWED] ");
    if (secondaryWeapon) secondaryWeapon->DisplayWeaponInfo();
    std::cout << "========================\n";
}