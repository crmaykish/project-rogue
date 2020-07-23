# Project Rogue

![Screenshot](/assets/screenshot.png)

## v0.1 Release Features
- [ ] Ten levels to descend with a final boss
- [x] One generic randomized class
- [x] Learn abilities from books
- [ ] Three enemy types with distinct stats and AI behavior
- [x] Five weapons
- [x] Two shields
- [x] Armor types: head, boots
- [x] Four weapon effects - 2 defend, 2 attack
- [ ] Inventory management (show item stats, drop items, etc.)
- [ ] Melee or ranged attacks depending on the equipped weapon - logic is there, just change the attack icon
- [x] Pure SDL2 implementation (remove SDL2_gpu)

## v0.1 Stretch Goals
[ ] Build a WASM version playable in the browser
[ ] Level completion rewards options

## Bugs
 - Some combinations of item effects can cause stack overflows from a feedback loop
 - Game creation can loop forever adding effects

## Brainstorming
- Tiles should have move-on effects that they apply to players. Then the players can update themselves rather than the tiles updating actors that are on them
- Collecting ingredients and upgrading weapons/skills might be more fun than a leveling/exp system

### Effect Ideas:
- [x] Retaliation
- [x] Life Steal
- [ ] Chain Lightning
- [ ] Poison Cloud
- [ ] Explosion (effect is working, damage over time/spreading fire is not)
- [x] Sacrifice - damage self on use
- [ ] Charm - convert target to friendly temporarily
- [ ] Summon Familiar - create a friendly companion

### Ability Ideas:
- [ ] Whirlwind
- [ ] Throw Grenade
- [ ] Invisibility
