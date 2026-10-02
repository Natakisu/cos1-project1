#include "Player.h"
#include "Enemy.h"

Player::Player(std::string name)
    : name(name), constitution(10), strength(10), agility(10), intellect(10), focus(10),
    maxHP(100), currentHP(100), maxSP(100), currentSP(100), maxMP(100), currentMP(100),
    primaryWeapon(nullptr), secondaryWeapon(nullptr), isPrimaryActive(true),
    isBlocking(false), isDodging(false) {
}

Player::~Player() 
{
    // Memory cleanup 
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
    if (!activeWeapon || currentSP < activeWeapon->GetAttackStaminaCost()) {
        return 0;
    }

    currentSP -= activeWeapon->GetAttackStaminaCost();
    int damage = activeWeapon->CalculateDamage(strength, agility, intellect, focus);

    target.TakeDamage(damage, activeWeapon->GetPostureDamage());
    return damage;
}

int Player::PerformHeavyAttack(Enemy& target) 
{
    Weapon* activeWeapon = GetActiveWeapon();
    if (!activeWeapon) return 0;

    int staminaCost = activeWeapon->GetAttackStaminaCost() * 2;
    if (currentSP < staminaCost) return 0;

    currentSP -= staminaCost;
    int damage = static_cast<int>(activeWeapon->CalculateDamage(strength, agility, intellect, focus) * 1.5f);

    target.TakeDamage(damage, activeWeapon->GetPostureDamage() * 2);
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