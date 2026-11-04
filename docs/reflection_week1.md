
# Week 1 Reflection

### 1. Code Quality Issues
[Before refactoring, one of the worst parts of the codebase was the monolithic structure of `Game::Initialize()` and the lack of synchronization in resource pools. The `Initialize` function was bloated, combining game state orchestration, character loading, fallback creation loops, and difficulty setups into a single massive routine, which made it difficult to maintain or debug. Additionally, allocating attribute points increased maximum health caps via `RecalculatePools()`, but left current health bars out of sync at baseline values, causing immediate stat mismatches during gameplay.]

### 2. Improvements Made
[To address these issues, I refactored `Game::Initialize()` by breaking it down into specialized helper routines (`LoadExistingGameSession`, `StartFreshGameSession`, and `SetupBossDifficulty`), which drastically improves readability and separated responsibilities cleanly. I also updated `Player::RecalculatePools()` to dynamically scale current health, stamina, and mana pools proportionally whenever attributes increase or save files are loaded. Furthermore, I hardened the weapon selection cleanup loops by implementing strict inequality checks and pointer-nullification guards to completely eliminate double-delete risks when assigning identical weapons.]

### 3. Refactoring Challenges
[While refactoring, the trickiest challenge was managing pointer lifecycles and ensuring that unselected dynamic weapon instances were cleaned up safely without triggering memory corruption or double-free errors. Fortunately, after carefully setting pointers to `nullptr` and adding slot validation checks, the code compiled cleanly and behaved stably during runtime. If I had more time to refactor next, I would focus on completely decoupling the console UI layout logic further from the core state loops and introducing a more robust inventory management array for multi-item equipment handling.]

### 4. Remaining Issues
[My primary objectives are to break up some of the oversized files to clean up the codebase. While doing that, I plan to smooth out the combat flow and streamline the menus to reduce unnecessary inputs without sacrificing readability. I also aim to fix the game loop so players can keep playing without the app closing.]