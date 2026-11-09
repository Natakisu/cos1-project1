
### 1. Feature Implementation

- Currency System (Relic Shards)
    
- The currency system is assigned to the player and is rewarded by defeating the boss. The higher the difficulty the higher the amount rewarded. It save to the player save file and is carried over between saves.

- Item Shop
    
- Not much point in earning currency as a reward if there isn't anything to do with it right? Added a shop that allows the player to spend their hard earned Relic Shards on potions and Legend of Zelda themed Magic Items (Why? Because, yes.). Every item properly does what it is supposed to do (heal, restore sp/mp, do damage and apply build ups). Currently debugging an issue where if there is more than 10 items in the player inventory any potion in a slot higher than 10 (11, 23, etc.) isn't properly consumed, but potions are properly consumed if not.

- Weapon Skills
    
- Been wanting to get the weapon skills added since the original brainstorm. It isn't really a New World / Souls game without weapon skills. Each weapon has two unique skills that have interactions between one another or reward the player with more hits for having higher stats. They are all working and properly adhere to the turn based cooldown. You cannot use a Skill that is still on cooldown.

---

### 2. Design Decisions

- I initial had already planned to add these feature, but wanted to get all the other feature added first since they wouldn't work properly without the other feature first (at least logically can't cast a weapon skill without a weapon).
    
- I believe the design and implementation match what I had originally planned. I did have to make minor tweaks to what the actual skill were/did because some either didn't make since, or have all the proper systems to work properly.

---

### 3. Challenges & Issues

- The biggest issue I had this week was trying to make different feature branches. I had accidently added some lines of code and pushed it to the incorrect branch, and then when i tried to fix it I accidently pulled from dev and not the right branch and it reset all the work I had been doing. I was able to get all the information pulled back where it needed to be and had to resolve quite a few conflicts.
    
- Even though I had originally thought I had gotten everything back together properly, when there is thousands of lines of code across 20 some files you end up missing things here and there. I was able to discover things that were still missing or not working properly. There was a neat little bug where you could still use and active the weapon skills, but the menu option to open them wasn't actually there.

---

### 4. Improvements to Your System

- With the weapon skills, currency, and item shop it feels like more of an RPG instead of a attack till something dies, repeat.
    
- The weapon skills help define a more specific playstyle and depth to the combat system and feel pretty rewarding and impactful. The currency reward from defeating the boss and a way to spend that currency adds more replay ability to the game given something to work towards beyond just taking on a harder boss. 

---

### 5. Looking Ahead

- I am going to keep working on the weapon skills and expanding on those, they don't all do exactly what I want them to do, but I'm still researching and experimenting with ways to implement all the logic into the code. I also plan to add more variety to the items available to purchase in the shop, and would like to also incorporate gear for the player to equip and upgraded weapons. A little bit of variety in the actual fights would be a nice improvement too, like having to fight more than one enemy at a time, or different enemies with different actions and tactics to help flesh out the gameplay and make it feel more like the RPGs everyone is used too.