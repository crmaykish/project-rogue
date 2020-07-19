#include "cm_combat.h"
#include "cm_actor.h"

namespace cm
{
    Combat::Combat(Actor &owner) : Owner(owner) {}

    void Combat::Damage(ActorDamage damage)
    {
        Owner.Stats.AdjustHP(-damage.Value);

        if (Owner.Stats.HP() == 0)
        {
            if (!Owner.Friendly)
            {
                Owner.Active = false;
            }
        }

        // Trigger on-defend effects for this actor
        Owner.EffectsComp->TriggerEffects(EffectTrigger::Defend, &Owner, damage.Source, nullptr);

        // Trigger on-attack effects of the attacker (if there is one)
        if (damage.Source != nullptr)
        {
            damage.Source->EffectsComp->TriggerEffects(EffectTrigger::Attack, damage.Source, &Owner, nullptr);
        }
    }

} // namespace cm
