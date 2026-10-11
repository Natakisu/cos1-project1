> Use this worksheet to plan the next phase of your project **before you begin coding**
> Be clear, specific, and intentional—this will guide your development this week.

---
## 📌 Project Overview

**Project Name:**
→   [The Relic Switcher (TBD)
  
**What does your program currently do? (1–3 sentences)**   
→ [Currently my program prompts the user for a name. After the user has entered their name they are given 30 attribute points to allocate into the attribute system that handles the scaling for different actions during the combat loop. The current combat loop is pretty basic, but give 6 user inputs to choose from Light Attack, Heavy Attack, Swap Weapon, Block, Dodge, and Inspect Weapon and the code can at a preliminary state handle those inputs properly, and accurately changes based on attribute allocation. ]

---
## 🔍 Current Progress Check  
  
**What is working right now?**   
→   [Right now, the turn-base combat loop is fully functional, including player attribute point allocation (with a limited 30-point pool for CON, STR, AGI, INT, and FOC), resource scaling for Max HP, SP, and MP, dual-weapon inventory inspection, and robust input validation on the console menu to catch invalid menu selections safely.]
  
**What is NOT working or incomplete?**   
→   [The boss's telegraphed intent system and posture stagger mechanic are currently set as placeholders, and the elemental status effect build-ups (such as Bleed or Burn) are not yet integrated into the combat loop.]
  
**What feels confusing or messy in your code?**   
→ [The console UI and the main `Game::RunCombatLoop()` switch-case logic are  a bit crowded and don't have much explanation to them as more options and weapon stats are added, meaning I will need to update the UI format and game logic  to be more cleanly separated into dedicated display helper methods soon.]

---
## 🚀 Feature Planning  
  
List the features you plan to add or improve this week.  
  
### Feature 1  
**Name:**   
→   [Telegraphed Boss Intent System]
  
**What does this feature do?**   
→  [At the beginning of each combat round, the boss decides on and displays a specific upcoming action (i.e. _Heavy Strike_, _Quick Sweep_, or _Blocking_). The player must read this previewed intent and choose a matching counter-action such as executing a dodge or defensive block to mitigate or reduce incoming damage.]
  
**Why is this feature important?**   
→   [It transforms the combat loop from a simple stat-check into a more of a strategic turn-based RPG experience, giving the player something to react to every turn rather than just trading blows blindly and hoping for the best (let's be honest though, we are all guilty of blinding charging into a boss fight and quickly regretting it soon after).]
  
---
### Feature 2  
**Name:**   
→   [Posture Stagger & Break Meter]
  
**What does this feature do?**   
→   [Implements a secondary posture meter for the boss that accumulates damage whenever the player successfully lands heavy attacks or counter-moves. When the posture meter fills completely, the boss enters a stunned/staggered state, skipping their next turn and opening them up to damage multipliers.]
  
**Why is this feature important?**   
→   [It rewards aggressive, precise weapon management and gives players a goal to work toward instead of just attacking and reacting during prolonged boss encounters, adding depth to the dual-weapon switching mechanics and keeping the game refreshing.]
  
---
  
### Feature 3 (optional)  
**Name:**   
→   [Elemental Status Effect Build-Up / Damage (Bleed / Burn)]
  
**What does this feature do?**   
→   [Tracks elemental or physical status build-up meters during combat. Consecutive attacks with specific weapons or attributes build up status meters on the enemy, triggering burst damage or debuffs once a threshold is reached.]
  
**Why is this feature important?**   
→   [It enhances the value of switching between primary and secondary weapons by encouraging players to mix weapon types to exploit enemy elemental vulnerabilities.]
  
---
## 🧩 System Design Updates  
  
**Will you need to create any new classes? If so, which ones?**   
→   [Yes, I am planning to create a dedicated `StatusEffect` class t to handle active debuffs, as well as a small utility manager to parse and evaluate boss intents each turn.]
  
**Will you modify any existing classes? How?**   
→   [- **`Enemy`:** Will be modified to include intent generation logic, a posture meter variable, and a method to check whether the boss is currently staggered.]
    
[- **`Player`:** Will be updated to handle reactive defensive triggers (like matching blocks or dodges against specific boss intents) and status accumulation tracking.]
    
[- **`Game`:** Will be modified to update the turn-resolution during combat loop, processing player actions, checking boss posture breaks, and status effect durations every round.]
  
**What data structures will you use (vectors, 2D vectors, etc.)?**   
→   [I will use `std::vector` collections to manage active inventory lists, status effects applied to characters, and round logs for combat feedback.]
  
---
## 🔄 Program Flow  
  
**Describe how a user interacts with your program:**  
  
1. Program starts →   [The application launches in the console, greets the player, and prompts them to enter a custom character name.]

2. User chooses →   [The player allocates their bonus attribute points across Constitution, Strength, Agility, Intellect, and Focus, then enters the combat loop where they select options from the action menu.]

3. Program responds →   [The console processes the selected action, calculates weapon damage scaled by character attributes, checks for input validation errors if invalid characters are typed, and displays updated player resource pools and boss health stats.]

4. Loop/next step →   [The boss executes its attack, status values and turn states reset, and the loop repeats until either the player or the boss is defeated.]
  
---
## 🎯 Usability Improvements  
  
How will you make your program easier to use this week?  
  
- Clearer prompts:   
→   [Provide dynamic, context-aware instructions during character stat allocation that display remaining points in real time so the player always knows their available budget.]
  
- Better error handling:   
→   [Expand input validation loops to catch non-numeric text and out-of-range choices across all custom menus rather than just the combat loop.]
  
- Improved menu/navigation:   
→   [Reorganize the combat console layout with clean section dividers and clear index numbers so navigating between attacks, weapon swapping, and stats is easy and readable.]
  
---
## ⚠️ Potential Challenges  
  
**What do you think will be the hardest part this week?**   
→   [The hardest part this week has been battling the flu, while also having to take care of kids that also have the flu and find time and energy to work on schoolwork.]
  
**What is your plan if you get stuck?**   
→   [I'm doing my best to get all the needed goals for milestone 2 complete at a basic level, and have reached out informing my course instructor informing her of my set back this week.]
  
---
  
## 📈 Level Up Goal  
  
**What skill are you focusing on improving this week?**   
→   [Object-oriented design patterns and state management across multiple classes (specifically handling interactions between `Game`, `Player`, and `Enemy`).]
  
**What will you do to improve it?**   
(e.g., tutorial, practice, debugging, office hours)   
→   [I will practice by mapping out class dependency diagrams on paper before coding, writing small, isolated unit test functions for each new state transition, and stepping through the execution flow in the debugger to verify how data passes between objects.]
  
---
## 🗓️ Task Breakdown (GitHub Issues Planning)  
  
List the tasks you plan to create as GitHub Issues:  
  
- [x]   [Update `Player` and `Game` to handle attribute system]
- [x]   [Update `Weapon` and `Game` to handle a basic weapon system]
- [x]   [Add stat scaling into the basic combat loop]
- [ ]   
  
---
  
## 🔥 Final Check  
  
Before you start coding, ask yourself:  
  
- [x] Do I know what I’m building this week?   
- [x] Do I know where to start?   
- [ ] Did I break my work into small tasks?   
  
If yes → start coding 🚀   
If no → refine your plan first   
  
---
## 😈 Final Thought  
  
> Plan it now… or debug it later.