### 🏷️ Project Title

[The Relic Switcher (TBD)

### 💡 Project Idea

[_The Relic Switcher_ is a C++ turn-based tactical combat simulator with elements from _New World: Aeternum_ and _Dark Souls_ featuring a dual-weapon swapping mechanic and a telegraphed boss intent system. Players take on (a) boss encounter(s) where they can dynamically swap between primary and secondary weapons on their turn to chain attacks, manage resource costs (Stamina and Mana), and exploit enemy elemental status vulnerabilities. The goal is to strategically react to telegraphed boss intents using offensive moves, defensive guards, and dodges while managing the boss's Posture meter (and possibly physical/elemental weaknesses) to trigger high-damage or stagger the boss.

### ⚙️ Core Features

- [ **1. Dynamic Dual-Weapon Swapping System:** Allows players to equip primary and secondary weapons and swap active weapon during combat at a Stamina cost to adapt to changing combat scenarios.
    
- [ **2. Telegraphed Boss Intent & Posture System:** Displays the boss's planned action at the start of each turn so players can strategically react (`Attack`, `Block`, `Dodge`), alongside a breakable Posture meter that staggers the boss when depleted.
    
- [ **3. Attribute-Based Damage & Resource Scaling:** Implements 5 core character attributes (`**CON**`, `**STR**`, `**AGI**`, `**INT**`, `**FOC**`) that directly govern character resource pools (HP, SP, MP) and scale weapon damage output based on weapon scaling ratios.

### 🧱 Class Plan

- [**`Player`:** Manages character attributes (`**CON**`, `**STR**`, `**AGI**`, `**INT**`, `**FOC**`), tracks active resource pools (`HP`, `SP`, `MP`), controls dual-weapon swapping, and executes player actions (`Light Attack`, `Heavy Attack`, `Block`, `Dodge`).
    
- [**`Weapon`:** Stores weapon metrics (base damage, posture damage, stamina/mana costs) and calculates scaled damage output based on character attribute ratios.
    
- [**`Enemy`:** Controls boss health, posture mechanics, status effect build-ups, generates telegraphed intents, and resolves boss actions against the player.
    
- [**`Game`:** Controls the main application initialization, character setup, combat menu rendering, and the core turn-resolution loop.

### 🎯 Current Focus

[My current focus is establishing the core turn-based combat loop inside `Game`, ensuring seamless interaction between player resource deduction, weapon scaling calculations, and boss intent resolution. After I am satisfied with the basic loop and know it is working I plan to start incorporating more of the systems I would like to have in the game (`Attribute System`, `Customizable Attributes`, `Weapon Skills`, `Experience System`, `Bleed and Burn Mechanics` and so on)