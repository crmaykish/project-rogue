# Project Rogue

![Screenshot](/assets/screenshot.png)

## Definitions
1. Actor - A character in the game (human or NPC) with a position, health, abilties etc.
2. Action - Something that an actor can attempt to do once (or more) per turn, e.g. move, pickup item, use ability, etc.
3. Ability - Skills that are tied to a specific actor, e.g. Healing Light, Cleave, Ranged Attack. May be targeted or self-cast
4. Effect - Changes something about a specific actor, e.g. Damage, Heal, RefillMana. This is something active, not a passive buff to stats.
5. Item - An actor can pickup, use, and equip items. Items can have base stats (damage, armor, resist, etc.) and effects.

## v0.1 Release Features
- [ ] Ten levels to descend with a final boss
- [ ] One generic randomized class
- [ ] Learn abilities from books
- [ ] Three enemy types with distinct stats and AI behavior
- [ ] Five weapons
- [ ] Two shields
- [ ] Two armor types for each of: head, chest, boots
- [ ] Inventory management (show item stats, drop items, etc.)
- [x] Pure SDL2 implementation (remove SDL2_gpu)

## v0.1 Stretch Goals
[ ] Build a WASM version playable in the browser


### Notes

Overcomplicated effects system

Start with a simple combat component for actors

When actors take damage, they trigger defend effects on the world or on their attacker

When actors do damage, they trigger attack effects on their target

Item effects will end up having know their owner? Unless we set the owner right before
we actually use the effect...

Make Effect only for secondary things, not the main mechanism of combat

Thought: Create a system like the stats system for Effects. Let the actor maintain a map of
trigger types to effects. The other subsystems can just attach or detach Effects when something
changes. Then an actor has a full list of effects for every trigger at the ready

Items, equipment, buffs, environment can all add/remove Effects to the actors with the same interface