## Feature 1: Consumable Item System & Inventory

- **Description:** Introduce a consumable inventory system where players can hold healing potions or status-clearing/causing items. The user accesses these items during combat through a new menu option to restore health or stamina mid-fight.
- **Why It Matters:** It introduces resource management outside of weapon actions, giving players tactical healing options beyond passive regeneration or defensive stalling.
- **Task Breakdown:**
		1. Create an `Item` class (or struct) to define consumable properties (name, effect type, heal/buff value). 
		2. Implement an inventory container vector inside the `Player` class to store acquired items. 
		3. Add a new combat menu option allowing players to open their inventory and consume items during their turn. 
		4. Write file-handling logic to save and load player inventory states alongside character attributes. 
		5. Test consumption mechanics and resource restoration caps during combat loops.

## Feature 2: Active Weapon Special Skills
- **Description:** Expand the weapon system by adding unique active special skills tied to each weapon type (e.g., a heavy posture-breaking slam for the Warhammer or a rapid bleed flurry for Daggers) that consume stamina or mana pools.
- **Why It Matters:** It deepens the combat mechanics by moving beyond basic light and heavy attacks, making weapon choices feel distinct and strategic.
- **Task Breakdown:**
	1. Update the `Weapon` class to include special skill attributes (mana/stamina cost, multiplier, status effect triggers). 
	2. Implement a skill execution function inside the `Player` or `Weapon` class to process resource deductions and damage calculations. 
	3. Add a new action choice to the combat menu for triggering the active weapon's special skill.
	4. Integrate status-effect buildup hooks so special skills apply high-tier burn or bleed stacks. 
	5. Test resource validation checks to ensure players cannot use skills when lacking stamina or mana.

## Feature 3: Currency & In-Game Item Shop
- **Description:** Add a currency system (e.g., "Relic Shards") earned by defeating bosses, alongside an inter-battle shop menu where players can spend currency on consumables, upgrades, or weapon enhancements.
- **Why It Matters:** It provides a rewarding progression loop between combat encounters, giving purpose to combat victories beyond just XP.
- **Task Breakdown:**
	1. Add a currency tracking variable to the `Player` class and update victory reward loops to grant currency upon boss defeat. 
	2. Create a shop management function (`Game::OpenItemShop()`) that lists available items for purchase. 
	3. Implement purchase validation logic to check if the player has enough currency and deduct it upon buying. 
	4. Integrate purchased items directly into the player's inventory container. 
	5. Test currency persistence by saving and loading balance amounts across game sessions.