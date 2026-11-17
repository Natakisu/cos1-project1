### [Bug 1: Unprotected Menu Inputs Causing Crashes on Invalid Data]

- **Description:**
    
    - **What happened:** Entering letters or unexpected symbols into menu choices caused input stream failures and unexpected loop behavior or crashes.
        
    - **Expected behavior:** The game should gracefully reject invalid non-numeric input, clear the stream error state, and prompt the user again without breaking execution.
        
- **Steps to Reproduce:** Launch any menu (such as the main combat or attribute allocation screen) and type letters instead of a number.
    
- **Cause:** Raw string-to-integer parsing via `std::stoi()` without try/catch error handling, along with standard stream extractions failing when encountering alphabetic characters.
    
- **Fix:** Created a centralized `GameInput::GetValidatedInt` method using `std::getline()`, `std::stoi()`, and robust `try/catch` blocks to catch `std::invalid_argument` and `std::out_of_range`, successfully enforcing valid bounds across all menus.

### [Bug 2: `WeaponSkillManager` Friendship and Private Member Access Failure]

- **Description:**
    
    - **What happened:** Compiling `WeaponSkills.cpp` threw multiple `C2248` errors stating that private player attributes (`strength`, `agility`, `intellect`, `focus`) could not be accessed.
        
    - **Expected behavior:** The skill manager should be able to read player stats to calculate dynamic weapon skill damage scaling.
        
- **Steps to Reproduce:** Attempted to build the project after separating `WeaponSkillManager` into its own file.
    
- **Cause:** The `Player` class lacked the `friend class WeaponSkillManager;` declaration, restricting external class access to its private core attributes.
    
- **Fix:** Added `friend class WeaponSkillManager;` inside `Player.h` to grant proper access rights for stat-scaling combat calculations.

### [Bug 3: Missing Defensive State Activation in Support Weapon Skills]

- **Description:**
    
    - **What happened:** Defensive and support skills like _Fortress Wall_, _Entomb_, and _Divine Plea_ triggered cooldowns and consumed resources, but did not actually apply their defensive buffs or healing.
        
    - **Expected behavior:** _Fortress Wall_ and _Entomb_ should trigger a 100% full block state (`FullBlock()`), while _Divine Plea_ should restore player health points (`Heal()`).
        
- **Steps to Reproduce:** Equip a Sword & Shield or Life Staff in combat, use their long/short skills, and observe that enemy incoming damage or low health remained unaffected.
    
- **Cause:** The skill implementation stubs only called cooldown triggers and resource deductions without invoking player state methods.
    
- **Fix:** Updated `WeaponSkillManager::ExecuteSwordAndShield`, `ExecuteIceStaff`, and `ExecuteLifeStaff` to explicitly invoke `player->FullBlock()`, `player->RestoreMP()`, and `player->Heal()` alongside resource consumption.