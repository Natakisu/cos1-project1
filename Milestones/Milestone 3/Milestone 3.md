- ⚙️ Features added

	-_**Readability Updates**_
	- [**Lambda-Driven Health & Resource Bars:** Added lambda functions (`drawBar`) inside `Game::RenderUI()` to dynamically compute and render visual status bars for player HP, SP, MP, and boss health.]
	
	- [**Custom Console Helper Library (`ConsoleHelper`):** Created a dedicated helper module (`ConsoleHelper.h` and `ConsoleHelper.cpp`) to handle structured text printing and TrueColor ARGB/RGB formatting across the terminal interface.]
	
	- [**Turn-Based Combat Flow Refinements:** Integrated explicit pause checkpoints and screen-clearing logic (`system("cls")`) into `Game::RunCombatLoop()` to clean up the console when a fight started and combat readouts, damage numbers, healing effects, and weapon swaps remain visible to the user before refreshing the UI every turn.]

	-_**Added Features**_
	- [**More Weapons:** Added more weapons besides the basic starting weapons so the user can actually select which weapons they want. This makes the attribute system feel more meaningful by increasing damage of weapons based on attribute allocation, and implementing healing for Focus weapons.]

- 🧱 Updates to your system design

	-**Menu Overhaul**
	-[**Main Menu:** Added a Main Menu that appears when starting the application so it feels more like a game instead of just jumping into asking the user for a name. I also included a menu selection to view the games instructions that provides a brief explanation of the game to help ease the user into the game.]
	
	-[**Weapon Menu:** When I originally added the new weapons to game game when you get done with naming your character and assigning your attributes it just word bombed all the weapons onto the console screen cause panic and chaos. I implemented a menu that allows the user to make a selection from the different attribute categories, and the once they make a selection it opens a new menu of the weapons solely in that attribute category. It helps declutter the console a bit, and makes it much easier to read and understand what is going on. I also included an option to display all weapons, because like Bethesda has shown us, Some bugs can be a feature.]
	-**Other Updates**
	-[As mentioned already above in features added I implemented more features to help make the UI easier to read. I also added a cls function to clean up the console once the boss fight has started and users get a read out of what actions are happening during each turn and have to hit enter to continue through the battle. I feel it definitely make it feel more like a game and helps give a clear understanding of what is happening when it happens, and make it feel more like your playing a game and not just an ASCII Hell console.]

- 🧹 Refactoring improvements

	-[**Improved Combat Readability & Timing:** Refactored `Game::RunCombatLoop()` to pause for user input after player actions and enemy turns, resolving an issue where the console was clearing too quickly to read combat text, healing amounts, or weapon swap confirmations.]
	
	-[**Clean Menu Output Control:** Standardized menu headers, instructions, and error warnings to use unified color definitions (`Cyan`, `Green`, `Red`, `White`) for consistency across the entire console application.]
	
	-[**Milestone 2 Feedback:** I also addressed the feedback about pointers and memory allocation throughout the code and implemented code to help clean those up and made sure I don't have any memory leaks, or unnecessary code laying around.]