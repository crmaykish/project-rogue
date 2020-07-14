# Project Rogue

![Mimic](/assets/mimic.gif) ![Mimic](/assets/mimic.gif) ![Mimic](/assets/mimic.gif)

![Screenshot](/assets/screenshot.png)

## Definitions
1. Actor - A character in the game (human or NPC) with a position, health, abilties etc.
2. Action - Something that an actor can attempt to do once (or more) per turn, e.g. move, pickup item, use ability, etc.
3. Ability - Skills that are tied to a specific actor, e.g. Healing Light, Cleave, Ranged Attack. May be targeted or self-cast
4. Effect - Changes something about a specific actor, e.g. Damage, Heal, RefillMana
5. Modifier - 
6. Item - An actor can pickup, use, and equip items. Items can have base stats (damage, armor, resist, etc.), effects and modifiers.

Items:

Item options:
1. Stat increases - HP, mana, light radius, etc
2. Chance on damage
3. Chance on take damage

weird stuff items could do:
spawn potions
destroy itself
double a stat temporarily
blind user or target
steal ability from target
grant an ability (permanent or charges)
invisibility
cursed item, cannot remove from inventory
life steal

Ability ideas:
regenerating health shield
reflect damage
knock back
stun
poison/bleed damage
chain lightning
piercing shot
spreading diseases

TODO:

Duplicating a lot of effort here. Maybe just have effects take user, target, and world.
Then make abilities/modifiers/etc just a collection of effects.