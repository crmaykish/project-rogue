# Project Rogue

![Screenshot](/assets/screenshot.png)

## v0.1 Release Features
- [ ] Ten levels to descend with a final boss
- [x] One generic randomized class
- [ ] Learn abilities from books
- [ ] Three enemy types with distinct stats and AI behavior
- [x] Five weapons
- [x] Two shields
- [x] Armor types: head, boots
- [ ] 5 weapon effects - 2 defend, 2 attack
- [ ] Inventory management (show item stats, drop items, etc.)
- [ ] Melee or ranged attacks depending on the equipped weapon
- [ ] Experience gain and stat/enemy scaling
- [x] Pure SDL2 implementation (remove SDL2_gpu)

## v0.1 Stretch Goals
[ ] Build a WASM version playable in the browser
[ ] Level completion rewards options

## Bugs
 - Maps occasionally spawn alternating wall tiles in a checkerboard pattern, why?
 - Some combinations of item effects can cause stack overflows from a feedback loop

## Brainstorming
- Tiles should have move-on effects that they apply to players. Then the players can update themselves rather than the tiles updating actors that are on them

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
