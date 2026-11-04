## 1. Class Review
### Class 1: `Game`
- **What is wrong with it:**
- *Structure:* It currently mixes game state management with console UI rendering and input parsing loops. 
- *Responsibility:* It is doing too much, violating single-responsibility principles by handling both core control and interface output. 
- **What I plan to change / Why:** I will extract all UI display logic into a dedicated `GameUI` class and move input collection and validation into `GameInput`. This will clean up `Game.cpp` and isolate state orchestration.

### Class 2: `Player`
- **What is wrong with it:**
- *Structure:* Stat pool calculations are rigid and fail to dynamically scale current health and resource pools when attributes or save files are updated.
- *Clarity:* Inconsistent naming conventions between pool updates and derived stat calculations.
- **What I plan to change / Why:** I will refactor `RecalculatePools()` to proportionally scale current pools alongside maximum attribute increases and standardize function naming.

---
## 2. Function Review
1. **`Game::Initialize()`**
	- **What is wrong:** It is too long and handles too many distinct tasks (file loading, fallback creation, weapon selection, and difficulty setups).
	- **What we will improve:** We will streamline the function flow and delegate setup sub-tasks to dedicated helper routines.

2. **`Game::WeaponSelectionMenu()`**
	- **What is wrong:** Contains repetitive nested logic and potential memory risks during unselected pointer cleanup.
	- **What I will improve:** I will refactor the selection loop to eliminate duplicate logic and secure weapon pointer disposal.

3. **`Player::RecalculatePools()`**
	- **What is wrong:** Only recalculates maximum caps without checking or adjusting current resource pools.
	- **What I will improve:** I will expand its logic to adjust current pools dynamically during attribute allocation.

---

## 3. Code Quality Issues
- **Naming Issue 1:** Inconsistent function naming for derived stats (`UpdateDerivedStats` vs `RecalculatePools`).
- **Naming Issue 2:** Vague temporary variables used during weapon filtering menus.
- **Structural Issue 1:** Mixed responsibilities inside the monolithic `Game` class handling both UI and state logic.
- **Structural Issue 2:** Shared weapon pointer cleanup logic that risks double-deletion vulnerabilities.

## Required Refactor Types Included:
- Reorganizing class responsibilities
- Breaking large functions into smaller ones
- Removing duplicate logic