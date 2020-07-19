#include "cm_combat.h"
#include "cm_actor.h"
#include "cm_game_world.h"

namespace cm
{
    Combat::Combat(Actor &owner) : Owner(owner) {}

    void Combat::Damage(ActorDamage damage, GameWorld &world)
    {
        Owner.Stats.AdjustHP(-damage.Value);

        if (Owner.Stats.HP() == 0)
        {
            if (!Owner.Friendly)
            {
                Owner.Active = false;
            }
        }

        world.AddCombatText({std::to_string(damage.Value), Owner.Position.X, Owner.Position.Y, ColorRed});

        // Trigger on-defend effects for this actor
        Owner.EffectsComp->TriggerEffects(EffectTrigger::Defend, &Owner, damage.Source, &world);

        // Trigger on-attack effects of the attacker (if there is one)
        if (damage.Source != nullptr)
        {
            damage.Source->EffectsComp->TriggerEffects(EffectTrigger::Attack, damage.Source, &Owner, &world);
        }
    }

} // namespace cm
