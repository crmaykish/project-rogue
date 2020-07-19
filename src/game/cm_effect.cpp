#include "cm_effect.h"
#include "cm_logger.h"
#include "cm_actor.h"

namespace cm
{
    static uint32_t EffectID = 0;

    // Effect Map

    void EffectMap::Add(EffectTrigger trigger, std::shared_ptr<Effect> effect)
    {
        Log("Adding effect", LOG_INFO);

        if (Effects.find(trigger) == Effects.end())
        {
            // Create the vector
            Effects.emplace(trigger, std::vector<std::shared_ptr<Effect>>());
        }

        // insert the effect
        Effects.at(trigger).emplace_back(std::move(effect));
    }

    void EffectMap::Remove(uint32_t effectId)
    {
        Log("Remove effect: " + std::to_string(effectId));

        // TODO:
    }

    // Effect Component

    void EffectComponent::TriggerEffects(EffectTrigger trigger, Actor *source, Actor *target, GameWorld *world)
    {
        if (Effects.find(trigger) == Effects.end())
        {
            return;
        }

        for (const auto &e : Effects.at(trigger))
        {
            e->Use(source, target, world);
        }
    }

    // Effect Base Class

    Effect::Effect() : Id(EffectID++) {}

    // Effect Implementations

    void RetaliationEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log("retaliate", LOG_INFO);

        target->CombatComp->Damage({2, source});
    }

} // namespace cm