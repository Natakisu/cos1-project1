# Relic Switcher 
## Project Overview
[**Relic Switcher**] is a console-based, turn-based tactical RPG written in C++ and inspired by the dual-weapon combat systems of *New World: Aeternum* and status build-ups of *Dark Souls*. Players create a character, allocate core attributes, equip two distinct weapons that can be swapped mid-battle, and fight through escalating enemy encounters and boss battles. The purpose of the project is to build a modular, crash-resistant C++ game engine from the ground up while delivering a strategic, resource-management combat experience directly in the terminal.

---
## Features 
### Character Creation & Stat Progression
Allows players to name their character, and distribute attribute points across Constitution, Strength, Agility, Intellect, and Focus, directly scaling weapon damage, resource pools, and combat effectiveness. 
### Dual-Weapon Combat & Active Swapping 
Enables players to equip two weapons, all with their own unique weapon skills, simultaneously and swap between them during combat turns, dynamically changing available weapon skills, resource costs (Stamina and Mana), and elemental or physical damage scaling. 
### Weapon Skills & Defensive Stances 
Supports unique active abilities per weapon—including hard hitting attacks, defensive blocks, and healing/support skills —complete with cooldown tracking, damage mitigation states, and boundary-clamped math to prevent integer overflow. 
### Inventory, Equipment & In-Game Shop 
Tracks player gold, consumables, and weapons, allowing players to purchase potions and magic items, and allows the use of healing or resource-restoring potions and magic items during combat. 
### Persistent Save & Load System 
Serializes the player's current stats, currency, inventory items, and progression to a local save file so sessions can be resumed across separate runs. 
### Input Validation & Crash Protection
Centralizes all menu and numeric prompts through validated input helpers (`GameInput`), preventing stream failures, infinite loops, or crashes when non-numeric or out-of-range inputs are entered.

--- 
## Save & Load System 
* **What Information Is Saved:** Character name, level, core attributes (Constitution, Strength, Agility, Intellect, Focus), current and maximum HP/MP/SP pools, gold balance, equipped weapons, inventory items, and encounter progression. 
* **Files Created/Used:** Data is stored in a plain-text save file (`savegame.txt` / player save file) created automatically in the application's working directory.
* **When Information Is Saved:** Progress is saved whenever the player defeats the boss, purchases an item in the shop, and after attribute allocation.
* **How to Load Saved Progress:** Launch the application and select **Load Game** from the title menu and enter the character name as entered when created to restore your previous character state and inventory. The `savegame.txt` file must be on the computer within the application files in order for it to properly load.
* **Missing File Behavior:** If no save file exists when attempting to load, the program safely catches the missing file, notifies the user in the console, and returns cleanly to the menu without crashing.

---

* ## How to Run the Program 
1. Clone or download this repository to your local machine. 
2. Open the Visual Studio solution file (`.sln` or `.slnx`) located in the project directory. 
3. Confirm that the startup project is set to **`COS1 - Project`** and the build configuration is set to **`Debug` | `x64`** (C++20 standard). 
4. Build the solution by pressing **`Ctrl + Shift + B`** (or selecting **Build > Build Solution** from the top menu). 
5. Run the application by pressing **`F5`** (Start Debugging) or **`Ctrl + F5`** (Start Without Debugging). 
6. Follow the on-screen numbered menu prompts in the console window to start a new game or load an existing save. *(Note: No external `.csv` or asset files are required to launch a new game; save files are generated automatically when you save.)*
* The application is made in such a way that all the user should need is the files, and Visual Studios (or another C++ supported IDE) to run the console.
---
## How to Use the Program 
* **Navigation:** All menus use numbered selections (`1`, `2`, `3`, etc.). Type the number corresponding to your choice and press **`Enter`**. 
* Gameplay Loop:  Begin by creating a character or loading a save. After creating a character or loading a save the player is then moved to the preparation hub menu. From the preparation hub menu, you can enter combat encounters, visit the shop to buy weapons, magic items, or potions, manage your equipped weapons, and allocate earned attribute points. There is also a `debug/cheat` menu that will reward to player with experience or gold to streamline testing features (will be removed or added to the item shop as a purchasable before release).
* **Combat Controls:** During your turn, select an action by number to perform a basic light or heavy attack, block, dodge, activate a weapon skill, inspect which weapon is currently equipped and see a brief description of it's weapon skills, swap to your secondary weapon, or use a consumable item. During combat their is a basic UI menu the displays the player's Health (HP), Stamina (SP), Mana (MP), and Level. The UI shows the Boss' Health, Build-ups (burn, bleed, frostbite), posture damage, and it's telegraphed intent for player to be able to react to incoming attacks. The is also a `debug/cheat` option to instant kill the boss (will also be removed or moved).
* **Saving & Exiting:** Upon completion of the boss fight the application will do one of two things. 
	* *Player Wins*: If the players win the fight it pops up a Victory screen that shows how much experience and gold they won, and if they leveled up / how many levels they earned and then saves the game. Afterward it goes to a menu selection that allows them to return to the preparation hub, or exit the application. The save is handled by the victory system so whichever choice doesn't ruin the progress made.
	* *Boss Wins*: if the boss defeats the player it instead shows the defeat menu. It gives a similar screen that anyone who has played a *Dark Souls* game has seen before, and then gives the option to return to the main menu, or restart the fight.

---
## Project Structure
### Core Classes:
- **`Game`:** Manages the primary application loop, menu routing, shop interactions, and progression between encounters.
    
- **`Player`:** Stores character attributes, HP/MP/SP pools, equipped weapons, inventory items, and damage/healing calculations.
    
- **`Enemy`:** Represents boss encounters, managing enemy health pool, attack patterns, damage taken, and turn actions.
    
- `WeaponManager`: Handles the creation of the weapons in the game, their descriptions, and defines the cooldown system for the weapon skills
	
- **`WeaponSkills`:** Encapsulates weapon-specific skill execution, resource cost checks and defensive state triggers.
    
- **`CombatMenuManager`:** Handles turn-by-turn combat UI rendering, action selection, and combat flow coordination.
    
- **`GameInput`:** Provides centralized, exception-safe numeric and menu input validation across the entire application.
    
- **`PlayerSaveManager`:** Handles file I/O serialization and deserialization for saving and loading character data.

---

## Technologies Used

- **C++ (C++20 Standard)**
    
- **Standard C++ Library** (`<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<algorithm>`, `<limits>`)
    
- ** Microsoft Visual Studio**
    
- **Git & GitHub** (Branching, Pull Requests, Issues, and GitHub Projects)

---

## Known Issues & Limitations
- **Single Save Slot:** The save system currently writes to a single save file rather than supporting multiple characters. You can create more than one save file, but each must be loaded individually by entering the name. It make it quite tedious to load your character, if you don't enter the name exactly as typed when created (spelling, capitalization, missing spaces or numbers, etc.) it won't be able to load. You can also end up completely overwriting your save file by creating a new character that has the same name as another character you already created.
    
- **Manual Save File Edits:** While missing save files are handled gracefully, manually editing or corrupting values inside of the .text save file can cause unexpected stat loading and crashes.
    
- **Console-Only Interface:** Gameplay runs strictly via text-based terminal menus without any graphics or audio effects.
	
- **Missing or Incomplete Weapon Interactions**: While many of the weapon skills work as intended there are still a few that I am still working out to get to the place they are supposed to be. The overall combat system also feels quite lackluster and feels more like a hit it until it dies than a genuine RPG.

---

![Project Screenshot]
![[Pasted image 20261120151707.png]]