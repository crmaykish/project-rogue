# Project Rogue

![Screenshot](/assets/screenshot.png)

## v0.1 Release Features
- [x] Ten levels to descend with a final boss
- [x] One generic randomized class
- [x] Learn abilities from books
- [x] Three enemy types with distinct stats and AI behavior
- [x] Five weapons
- [x] Two shields
- [x] Armor types: head, boots
- [x] Four weapon effects - 2 defend, 2 attack
- [x] Melee or ranged attacks depending on the equipped weapon
- [x] Pure SDL2 implementation (remove SDL2_gpu)
- [ ] Inventory management (show item stats, drop items, etc.)
- [ ] Game balancing - actor stats, loot drop rates, map parameters etc.

## v0.1 Stretch Goals
[ ] Build a WASM version playable in the browser
[ ] Level completion rewards options

## Bugs
 - Some combinations of item effects can cause stack overflows from a feedback loop (lifesteal)

## Brainstorming
- Tiles should have move-on effects that they apply to players. Then the players can update themselves rather than the tiles updating actors that are on them
- Collecting ingredients and upgrading weapons/skills might be more fun than a leveling/exp system
- Maybe have shrines spawn randomly where you can trade in currency for upgrades. Or maybe just upgrade a skill or an item only once and somewhat randomly

### Effect Ideas:
- [x] Retaliation
- [x] Life Steal
- [ ] Chain Lightning
- [x] Poison Cloud
- [ ] Explosion (effect is working, damage over time/spreading fire is not)
- [x] Sacrifice - damage self on use
- [ ] Charm - convert target to friendly temporarily
- [ ] Summon Familiar - create a friendly companion
- [ ] Silenced - reduce energy to 1 for 3 turns

### Ability Ideas:
- [ ] Whirlwind
- [ ] Throw Grenade
- [ ] Invisibility
- Degenerating shield - acts like temporary HP
- Slow moving blast wave or line that ticks each turn

### Enemies
- Ghosts are slow, but can teleport
- Slimes split into smaller slimes when killed
- Spiders spit poison from a distance and then run away

### Synergies
- More fire damage for every on-fire tile around you
- Burning targets take more fire damage
- Healing has a chance to heal again