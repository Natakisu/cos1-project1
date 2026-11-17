#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Enemy.h"
#include "ConsoleHelper.h"
#include "WeaponSkills.h"
#include "PlayerSaveManager.h"

// --- CONSTRUCTORS & DESTRUCTOR ---
Player::Player(std::string name)
    : name(name),
    constitution(10),
    strength(10),
    agility(10),
    intellect(10),
    focus(10),
    maxHP(100),
    currentHP(100),
    maxSP(100),
    currentSP(100),
    maxMP(100),
    currentMP(100),
    primaryWeapon(nullptr),
    secondaryWeapon(nullptr),
    isPrimaryActive(true),
    isBlocking(false),
    isFullBlocking(false),
    isDodging(false),
    level(1),
    currentXP(0),
    xpToNextLevel(100),
    unspentAttributePoints(0),
    relicShards(100)
{
    RecalculatePools();
    currentHP = maxHP;
    currentSP = maxSP;
    currentMP = maxMP;
}

Player::~Player()
{
    delete primaryWeapon;
    delete secondaryWeapon;
    primaryWeapon = nullptr;
    secondaryWeapon = nullptr;
}

// --- ATTRIBUTES & POOL MANAGEMENT ---
void Player::AllocateAttributes(int conPoints, int strPoints, int agiPoints, int intPoints, int focPoints)
{
    constitution += conPoints;
    strength += strPoints;
    agility += agiPoints;
    intellect += intPoints;
    focus += focPoints;
    RecalculatePools();
}

void Player::SetAttributes(int con, int str, int agi, int intel, int foc)
{
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

void Player::DisplayStats() const
{
    system("cls");

    ConsoleHelper::print("--- " + name + "'s Attributes ---", ConsoleHelper::Cyan);
    std::cout << "Constitution (CON): " << constitution << " (Max HP: " << maxHP << ")\n";
    std::cout << "Strength     (STR): " << strength << "\n";
    std::cout << "Agility      (AGI): " << agility << " (Max SP: " << maxSP << ")\n";
    std::cout << "Intellect    (INT): " << intellect << " (Max MP: " << maxMP << ")\n";
    std::cout << "Focus        (FOC): " << focus << "\n";
    ConsoleHelper::print("---------------------------\n", ConsoleHelper::Cyan);

    ConsoleHelper::print("Press Enter to continue...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}

void Player::RecalculatePools()
{
    int oldMaxHP = maxHP;
    int oldMaxSP = maxSP;
    int oldMaxMP = maxMP;

    maxHP = constitution * 10;
    maxSP = agility * 10;
    maxMP = intellect * 10;

    currentHP += (maxHP - oldMaxHP);
    currentSP += (maxSP - oldMaxSP);
    currentMP += (maxMP - oldMaxMP);

    // Clamps to ensure values remain within bounds
    if (currentHP > maxHP) currentHP = maxHP;
    if (currentSP > maxSP) currentSP = maxSP;
    if (currentMP > maxMP) currentMP = maxMP;
    if (currentHP < 0) currentHP = 0;
    if (currentSP < 0) currentSP = 0;
    if (currentMP < 0) currentMP = 0;
}

void Player::UpdateDerivedStats()
{
    RecalculatePools();
}

// --- WEAPONS & LOADOUT ---
void Player::EquipWeapons(Weapon* primary, Weapon* secondary)
{
    primaryWeapon = primary;
    secondaryWeapon = secondary;
}

void Player::InspectWeapons() const
{
    system("cls");

    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("               [ LOADOUT & WEAPON SKILLS ]        ", ConsoleHelper::Cyan);
    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);

    auto printWeaponDetails = [](Weapon* weapon, bool isActive) {
        if (!weapon) return;

        if (isActive) ConsoleHelper::print("[ACTIVE] ", ConsoleHelper::Green, false);
        else std::cout << "[STOWED] ";

        std::cout << weapon->GetName() << "\n";

        std::string wName = weapon->GetName();
        std::string shortName = "Short Skill";
        std::string shortDesc = "Quick tactical strike.";
        std::string longName = "Long Skill";
        std::string longDesc = "Devastating signature technique.";

        if (wName == "Warhammer") {
            shortName = "Crushing Blow"; shortDesc = "Deals heavy STR damage and moderate posture damage (2 Turn CD)";
            longName = "Earthshatter"; longDesc = "Slams the ground for massive damage and heavy disruption (4 Turn CD)";
        }
        else if (wName == "Sword & Shield" || wName == "Sword and Shield") {
            shortName = "Shield Bash"; shortDesc = "Strikes the foe and guards posture (2 Turn CD)";
            longName = "Fortress Wall"; longDesc = "Raises an absolute defense aura for the turn (3 Turn CD)";
        }
        else if (wName == "Daggers") {
            shortName = "Flurry Strike"; shortDesc = "Delivers 3 rapid stabs with moderate Bleed buildup (2 Turn CD)";
            longName = "Shadow Step"; longDesc = "Vanish into shadows to auto-dodge and inflict high Bleed (4 Turn CD)";
        }
        else if (wName == "Bow") {
            shortName = "Quick Shot"; shortDesc = "Fires a swift arrow and prepares an evasive dodge (1 Turn CD)";
            longName = "Rain of Arrows"; longDesc = "Unleashes a multi-turn barrage of steady pressure (4 Turn CD)";
        }
        else if (wName == "Fire Staff") {
            shortName = "Fireball"; shortDesc = "Hurls a blazing sphere with moderate Burn buildup (2 Turn CD)";
            longName = "Combustion"; longDesc = "Detonates current target heat for massive scaling damage (4 Turn CD)";
        }
        else if (wName == "Ice Staff") {
            shortName = "Ice Spike"; shortDesc = "Hurls piercing ice with moderate Frostbite buildup (1 Turn CD)";
            longName = "Entomb"; longDesc = "Encases you in crystal ice for safety and MP recovery (4 Turn CD)";
        }
        else if (wName == "Life Staff") {
            shortName = "Divine Plea"; shortDesc = "Offers a brief prayer to restore moderate HP (2 Turn CD)";
            longName = "Sacred Ground"; longDesc = "Consecrates the earth for sustained healing and protection (4 Turn CD)";
        }
        else if (wName == "Greatsword") {
            shortName = "Relentless Onslaught"; shortDesc = "Unleashes multi-hits scaling off your Agility (2 Turn CD)";
            longName = "Execute"; longDesc = "A devastating finisher scaling heavily off Strength (4 Turn CD)";
        }
        else if (wName == "Rapier") {
            shortName = "Evade Stance"; shortDesc = "Strikes scaling off target Bleed while dodging (2 Turn CD)";
            longName = "Detonate Stance"; longDesc = "Explodes target Burn buildup while regenerating MP (2 Turn CD)";
        }
        else if (wName == "Flail & Shield" || wName == "Flail and Shield") {
            shortName = "Blessed Aegis"; shortDesc = "Blocks incoming attacks and restores HP based on Focus (2 Turn CD)";
            longName = "Divine Smite"; longDesc = "Smites the foe with heavy damage and a health pulse (4 Turn CD)";
        }

        std::cout << "   -> Short: " << shortName << " (" << shortDesc << ")\n";
        std::cout << "   -> Long:  " << longName << " (" << longDesc << ")\n\n";
        };

    if (primaryWeapon) printWeaponDetails(primaryWeapon, isPrimaryActive);
    if (secondaryWeapon) printWeaponDetails(secondaryWeapon, !isPrimaryActive);

    ConsoleHelper::print("==================================================", ConsoleHelper::Cyan);
    ConsoleHelper::print("\nPress Enter to continue...", ConsoleHelper::White, false);
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool Player::SwapWeapon()
{
    if (currentSP < 10) return false;

    isPrimaryActive = !isPrimaryActive;
    currentSP -= 10;
    return true;
}

bool Player::ExecuteWeaponSkill(bool isLongSkill, Enemy& target)
{
    return WeaponSkillManager::ExecuteSkill(this, isLongSkill, target);
}

// --- COMBAT ACTIONS & RESOURCE MANAGEMENT ---
int Player::PerformLightAttack(Enemy& target)
{
    Weapon* activeWeapon = GetActiveWeapon();
    if (!activeWeapon) return 0;

    std::string weaponName = activeWeapon->GetName();

    if (weaponName == "Life Staff")
    {
        int healingAmount = 25 + (focus * 2);
        RestoreHP(healingAmount);
        ConsoleHelper::print(" > " + name + " channels the Life Staff, restoring " + std::to_string(healingAmount) + " HP!", ConsoleHelper::Green);
        return 0;
    }

    if (currentSP < activeWeapon->GetAttackStaminaCost())
    {
        ConsoleHelper::print("[!] Not enough stamina for light attack!", ConsoleHelper::Red);
        return 0;
    }

    currentSP -= activeWeapon->GetAttackStaminaCost();
    int damage = activeWeapon->CalculateDamage(strength, agility, intellect, focus);
    if (damage < 0) damage = 0;

    target.TakeDamage(damage, activeWeapon->GetPostureDamage());

    if (weaponName == "Flail and Shield" || weaponName == "Flail & Shield")
    {
        if (focus >= 12)
        {
            int drainHeal = 10 + focus;
            RestoreHP(drainHeal);
            ConsoleHelper::print(" [+] Flail & Shield life-drain active! Restored " + std::to_string(drainHeal) + " HP.", ConsoleHelper::Green);
        }
        else
        {
            ConsoleHelper::print(" [-] Focus too low (<12 FOC) to trigger Flail life-drain!", ConsoleHelper::Red);
        }
    }

    return damage;
}

int Player::PerformHeavyAttack(Enemy& target)
{
    Weapon* activeWeapon = GetActiveWeapon();
    if (!activeWeapon) return 0;

    std::string weaponName = activeWeapon->GetName();

    if (weaponName == "Life Staff")
    {
        int healingAmount = 50 + (focus * 4);
        RestoreHP(healingAmount);
        ConsoleHelper::print(" > " + name + " heavily channels the Life Staff, restoring " + std::to_string(healingAmount) + " HP!", ConsoleHelper::Green);
        return 0;
    }

    int staminaCost = activeWeapon->GetAttackStaminaCost() * 2;
    if (currentSP < staminaCost)
    {
        ConsoleHelper::print("[!] Not enough stamina for heavy attack!", ConsoleHelper::Red);
        return 0;
    }

    currentSP -= staminaCost;

    int rawDmg = activeWeapon->CalculateDamage(strength, agility, intellect, focus);
    int damage = (rawDmg * 3) / 2;
    if (damage < 0) damage = 0; // Prevent overflow/underflow wrapping

    target.TakeDamage(damage, activeWeapon->GetPostureDamage() * 2);

    if (weaponName == "Flail and Shield" || weaponName == "Flail & Shield")
    {
        if (focus >= 12)
        {
            int drainHeal = 20 + (focus * 2);
            RestoreHP(drainHeal);
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
    isFullBlocking = false;
    isDodging = false;
}

void Player::TakeDamage(int damage)
{
    if (isDodging || isFullBlocking) return;
    if (damage < 0) damage = 0;

    if (isBlocking)
    {
        damage /= 2;
    }

    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;
    if (currentHP > maxHP) currentHP = maxHP;
}

void Player::RestoreHP(int amount)
{
    if (amount < 0) amount = 0;
    currentHP = std::min(maxHP, currentHP + amount);
}

void Player::RestoreMP(int amount)
{
    if (amount < 0) amount = 0;
    currentMP = std::min(maxMP, currentMP + amount);
}

void Player::RestoreSP(int amount)
{
    if (amount < 0) amount = 0;
    currentSP = std::min(maxSP, currentSP + amount);
}

// --- PROGRESSION & REWARDS ---
void Player::GainXP(int amount)
{
    currentXP += amount;

    int safetyCounter = 0;
    const int maxLevelsPerGrant = 50;

    while (currentXP >= xpToNextLevel && safetyCounter < maxLevelsPerGrant)
    {
        currentXP -= xpToNextLevel;

        level++;
        unspentAttributePoints += 5;

        xpToNextLevel = static_cast<int>(xpToNextLevel * 1.5f);

        ConsoleHelper::print("\n========================================", ConsoleHelper::Cyan);
        ConsoleHelper::print("          [ LEVEL UP! ]                 ", ConsoleHelper::Green);
        ConsoleHelper::print(" You reached Level " + std::to_string(level) + "!", ConsoleHelper::White);
        ConsoleHelper::print(" You gained 5 unspent attribute points!", ConsoleHelper::Yellow);
        ConsoleHelper::print("========================================", ConsoleHelper::Cyan);

        safetyCounter++;
    }
}

// --- SAVE & LOAD OPERATIONS ---
void Player::SaveToFile(const std::string& filename) const
{
    PlayerSaveManager::Save(this, filename);
}

void Player::LoadFromFile(const std::string& filename)
{
    PlayerSaveManager::Load(this, filename);
}