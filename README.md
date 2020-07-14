# Project Rogue

![Mimic](/assets/mimic.gif) ![Mimic](/assets/mimic.gif) ![Mimic](/assets/mimic.gif)

![Screenshot](/assets/screenshot.png)

## Definitions
1. Actor - A character in the game (human or NPC) with a position, health, abilties etc.
2. Action - Something that an actor can attempt to do once (or more) per turn, e.g. move, pickup item, use ability, etc.
3. Ability - Skills that are tied to a specific actor, e.g. Healing Light, Cleave, Ranged Attack. May be targeted or self-cast
4. Effect - Changes something about a specific actor, e.g. Damage, Heal, RefillMana. This is something active, not a passive buff to stats.
5. Item - An actor can pickup, use, and equip items. Items can have base stats (damage, armor, resist, etc.) and effects.

TODO:

Items can:
1. Increase their own stats (damage, armor, resist, etc.)
2. Buff the actor's stats (HP, mana, light radius, etc.)
3. Chance on hit effects (give damage)
4. Chance on block effects (take damage)
5. Chance on kill effects
6. Grant abilities (or charges of abilities)

Abilities can:
1. Damage
2. Heal
3. Apply Buffs/debuffs
4. Change actor flags (blind, stun, freeze, fear, etc.)
5. Manipulate the world (change tiles)