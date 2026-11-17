
# Week 3 Reflection — Debugging & Stability

## 1. Bugs & Issues
This week, I uncovered and resolved four primary bugs in my C++ RPG (*Relic Switcher*): 
1. **Unprotected Menu Inputs:** Typing letters or non-numeric characters into combat and attribute allocation menus caused `std::stoi()` exceptions and stream failures that crashed the game loop.
2. **`WeaponSkillManager` Private Access Errors:** Separating weapon skill logic into its own class triggered `C2248` compiler errors because `WeaponSkillManager` lacked access to `Player`'s private stat attributes (`strength`, `agility`, `intellect`, `focus`). 
3. **Missing Defensive & Support Skill Effects:** Defensive abilities like *Fortress Wall* and *Entomb* consumed resources and triggered cooldowns, but failed to activate the player's `FullBlock` state, while *Divine Plea* did not trigger health restoration. 
4. **Integer Overflow & Health Wrap-Around:** Executing high-scaling heavy attacks (such as with the Ice Staff) caused damage calculations to overflow signed integer limits, displaying massive negative damage numbers and wrapping the boss's current HP bar into the hundreds of thousands before instantly defeating them on the next hit.

The **integer overflow and health wrap-around bug** was the most difficult to diagnose and fix because the symptoms appeared erratic at first—a single attack seemed to both heal the boss to an impossible number and then kill them on the follow-up hit. Tracing the arithmetic back to `Enemy::TakeDamage` and `Player::PerformHeavyAttack` revealed how unchecked negative values and signed integer wrapping corrupted the health pool.

## 2. Debugging Process 
My debugging strategy focused on isolating systems and tracing state changes step-by-step. Whenever an unexpected behavior occurred in combat, I examined the exact sequence of method calls between `Game.cpp`, `Player.cpp`, and `Enemy.cpp`, verifying how parameters were passed and modified at each step. Using Visual Studio's compiler diagnostics (`C2248`, `C2665`, `C2084`) alongside targeted playtesting allowed me to pinpoint whether an issue stemmed from class architecture, missing state toggles, or unchecked math boundaries. Breaking monolithic code into dedicated manager classes (`GameInput`, `WeaponSkillManager`, `CombatMenuManager`) also made it significantly easier to isolate and patch bugs without introducing side effects elsewhere.

## 3. Testing & Failures 
To test system stability, I intentionally tried to break the game using edge-case inputs and extreme combat scenarios. I entered alphabetic characters, symbols, and out-of-bounds numbers into every menu prompt, attempted to use skills and swap weapons without enough Stamina or Mana, and repeatedly triggered heavy attacks and defensive stances during boss encounters. Before my fixes, typing a single letter at a menu prompt immediately crashed the application, and scaling stats too high during heavy attacks broke the boss's health bar math.

## 4. Improvements Made 
The game is dramatically more stable and resilient now than it was after week 2. Centralizing all numeric input through `GameInput::GetValidatedInt` and `GetValidatedChoice` made the biggest immediate impact on user-facing stability, completely eliminating crashes from invalid keyboard input across every menu. Adding strict boundary clamping (`std::max` / `std::min` and `0` floor checks) inside `Enemy::TakeDamage`, `Player::TakeDamage`, and `Player::PerformHeavyAttack` also ensured that combat math remains reliable regardless of how high player stats scale.

## 5. Looking Ahead 
Because I completed the entire week's worth of debugging, documentation, and stabilization work in a single night, I will continue monitoring and addressing any lingering Week 3 edge cases alongside my upcoming Week 4 tasks. Specifically, a few potential issues still exist around external file handling and complex multi-turn status interactions—such as handling partially corrupted save files in `PlayerSaveManager` or stacking multiple status effects simultaneously on higher difficulties. As I move into Week 4 and beyond, I also plan to thoroughly stress-test damage formulas across every weapon and difficulty tier and expand the save system to support multiple save slots with file validation.