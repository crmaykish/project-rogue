#include <algorithm>
#include "cm_effect.h"
#include "cm_logger.h"
#include "cm_actor.h"
#include "cm_game_world.h"

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

        for (auto &e : Effects)
        {
            e.second.erase(std::remove_if(e.second.begin(),
                                          e.second.end(),
                                          [=](auto &a) { return a->GetId() == effectId; }),
                           e.second.end());
        }
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

    uint32_t Effect::GetId() { return Id; }

    // Effect Implementations

    void RetaliationEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log(source->Name + " retaliates", LOG_INFO);

        target->CombatComp->Damage({2, source}, *world);
    }

    void ExplosionEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {

        // Set all of the neighboring tiles on file

        auto neighbors = world->GetLevel()->GetNeighbors(target->Position.X, target->Position.Y, true);

        for (auto t : neighbors)
        {
            if (t != nullptr)
            {
                t->Fire = true;
            }
        }
    }

} // namespace cm