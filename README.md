# 🚀 Welcome to Project & Portfolio!

This repository will be used to keep track of research and development conducted in this class. Follow the instructions below to get started.
cos
### Getting Started

**1.** Review the [About](./docs/01_about/README.md) README and all of the links it provides.

**2.** Review the documentation and [Getting Started](./docs/02_getting_started/README.md) steps in this repository's docs folder.

**3.** Attend the first Live Lecture to see a live setup demo. If you are unable to attend, make sure to watch the archive.

### Next Steps...

After completing the above steps, feel free to begin updating this readme where indicated below. Remember to update this document each week to receive proper credit for the weekly Milestone assignment.

<br>

> ❗️ &nbsp; Now that you have read to this point, go ahead and delete this sentence and everything above it.

<br>

# Project & Portfolio 1

### Student First & Last Name

Hello my name is [enter name]. I am a student from [where are you from?]. The purpose of this repository is to practice development using version control. This work will help me begin to build a portfolio of skills and accomplishment that can be shared in the future.

<br>

## 📢 &nbsp; Weekly Stand Up

Each week I will summarize my milestone activity and progress by writing a stand-up. A stand-up is meant to be a succinct update on how things are going. Use these prompts as a guide on what to write about:

⚙️ Overview - What I worked on this past week

🌵 Challenges - What problems did I have & how I'm addressing them

🏆 Accomplishments - What is something I "leveled up" on this week

🔮 Next Steps - What I plan to prioritize and do next

<br>

### Week 1

⚙️ Overview - What I worked on this past week:

[So far this week, I have started working on what I want to create for my project and writing and testing the basic code structure for my game,
A tactical, turn-based C++ console RPG featuring real-time action combat mechanics inspired by _Dark Souls and New World: Aeternum_. Players manage Stamina and Mana across a dual-weapon swapping system to execute strategic Light/Heavy attacks, block or dodge telegraphed boss actions, and inflict threshold-based status effects (Bleed, Burn, Frostbite) to break enemy Posture.

🌵 Challenges - What problems did I have & how I'm addressing them

[I had set up the Git repo Starter files incorrectly, and I spent a good 3 to 4 hours working up a brainstorm and fleshing out the mechanics of the game and how I planned to implement them. I tried to fix the Starter Files, and ended up somehow deleting the 3-4 hours of work and having to start over because I was just typing out ideas in a .txt file in Visual Studio. I now believe I have fixed the Starter Files and have restarted fleshing out the game and planning my ideas. I am still putting them in a .txt file (just to make it easier for me when I get to the coding part), BUT I'm typing it out in a separate Word Document (plan to switch to Obsidian when I get a better understanding of how to use it), and having Google Gemini help format it from the Word Document to a Markdown style to put into the .txt file.

🏆 Accomplishments - What is something I "leveled up" on this week

[Definitely learned why something like Version Control is really important and useful, because instead of starting over completely, I could have figured out how to pull back the brainstorm.txt file I pushed a couple of times, but I hadn't even thought of that. Going through some trial and error and doing my best to dance in the fire, even though the healer is screaming at me not to.

🔮 Next Steps - What I plan to prioritize and do next

[I want to start getting my code built for all the basic systems I will need to even get my game running ( i.e., Player Class, Enemy Class, Basic Combat Loop). Once I can get all that figured out and working properly, I'll start implementing some of the systems that aren't needed to run the game, but make the combat more like I want it to (Weapons, Items, Blocking/Dodging) into the program

### Week 2

⚙️ Overview - What I worked on this past week:

[This week, I focused on implementing the manual attribute allocation system with a point cap for core stats (CON, STR, AGI, INT, FOC), refining weapon inspection details in combat, and building input validation to prevent console crashes.]

🌵 Challenges - What problems did I have & how I'm addressing them

[My biggest challenge this week was dealing with illness, which significantly limited my development time and focus. I addressed this by keeping my goals scoped strictly to the core attribute allocation and input fixes, breaking the work down into short, high-efficiency coding blocks when I had the energy.]

🏆 Accomplishments - What is something I "leveled up" on this week

[I successfully implemented a constrained point-buy pool system for character stats and fixed state-retention issues ensuring every new session initializes cleanly.]

🔮 Next Steps - What I plan to prioritize and do next

[Next, I plan to focus on implementing the telegraphed boss intent and reactive defense system, along with tracking boss posture stagger meters.]

### Week 3

⚙️ Overview - What I worked on this past week:

[Focused on expanding and balancing combat loop mechanics in _Relic Switcher_, adding player weapon selection menu, increased the boss' HP so he doesn't die so quickly, and added healing-based scaling. Specifically, implemented life-drain and healing thresholds for the _Life Staff_ and _Flail and Shield_, tuned Focus (FOC) requirements to 12 for the _Flail and Shield_ life-drain to activate, and worked on cleaning up the console UI by expanding on boarder, menu, and added basic colors to break up the black and white ASCII Hell and addressed feedback from Milestone 2 regarding dynamic allocations, pointers, and memory leaks. ALSO a Main Menu with an Instructions page.]

🌵 Challenges - What problems did I have & how I'm addressing them

[- **Challenge 1:** Dealing with a logic flow issue where player healing felt like it wasn't registering because the boss's attack seemed to cancel out the health gain on the same turn.
    
[- **Solution:** Added clear, explicit damage and healing readouts  and refactored turn logging so that damage taken and recovery numbers can be directly tracked turn-by-turn to easily verify and show the heal actually does something. As long as you remember you CANNOT increase your max HP through healing. No matter how much you heal for it does not take you above the threshold.]

[- **Challenge 2:** When I had originally created the weapon selection menu the console just got completely word bombed right after the user finished allocating their stats. Needless to say it made it very confusing and impossible to read. Was like Gojo just used Limitless on you.]
    
[- **Solution 2:** I decided to create a loop inside of a loop to handle sub menus within the weapon selection.]

[- **Challenge 3:** Added cls to clear the screen when starting the combat loop, but inadvertently made the boss immortal, and made it to where you could no longer see what damage and healing was being done, and you couldn't inspect weapons and swap anymore because of it]
    
[- **Solution 3:** Added a pause statement into the CombatLoop to display the information that happened based on user input and require confirmation before clearing the screen and showing the updated information.]

🏆 Accomplishments - What is something I "leveled up" on this week

[Leveled up my implementation refactoring by cleaning up  the console UI and user experience by adding menus, warnings, and success states visual identities, making the text-based RPG much more readable and immersive. I also got a refresher course and learned some new techniques for handling loops within loops and being able to carry over information when switching between the loops.]

🔮 Next Steps - What I plan to prioritize and do next

[I plan to start working on the Burn and Bleed statuses and their interactions next as well as continue refining the console UI to keep making it more readable and understandable. I'm also going to start getting started on implementing elements for Milestone 4, and adding more feature to my game. I feel the Experience System I have planned is really going to be elevated a file save-load/read/write system. Maybe add a menu for user's to input their own values for the boss' HP, or a difficulty selection. I don't know we'll see how much I can squeeze in.]

### Week 4

⚙️ Overview - What I worked on this past week:

[]

🌵 Challenges - What problems did I have & how I'm addressing them

[]

🏆 Accomplishments - What is something I "leveled up" on this week

[]

🔮 Next Steps - What I plan to prioritize and do next

[]