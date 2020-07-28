#include <set>
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
        // Set all of the neighboring tiles on fire
        auto actor = target != nullptr ? target : source;
        auto neighbors = world->GetLevel()->GetNeighbors(actor->Position.X, actor->Position.Y, true);

        for (auto t : neighbors)
        {
            if (t != nullptr)
            {
                t->OnFire = t->Flammability;
            }
        }
    }

    void LifeStealEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log(source->Name + " steals life from " + target->Name, LOG_INFO);

        // TODO: can't steal more life than the target has
        target->CombatComp->Damage({2, source}, *world);
        source->CombatComp->Heal({2, target}, *world);
    }

    void HealEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log(source->Name + " healing", LOG_INFO);
        source->CombatComp->Heal({4}, *world);
    }

    void SacrificeEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log(source->Name + " sacrifices", LOG_INFO);
        source->CombatComp->Damage({3}, *world);
    }

    void LearnAbilityEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        Log(source->Name + " learns random ability", LOG_INFO);

        auto freeSlot = source->AbilitiesComp->FreeSlot();

        if (freeSlot >= 0)
        {
            // TODO: make sure the ability is something the actor doesn't already know
            source->AbilitiesComp->SetAbility(freeSlot, RandomAbility());
        }
    }

    void PoisonAuraEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        for (auto n : world->GetLevel()->GetNeighbors(source->Position.X, source->Position.Y, true))
        {
            if (n != nullptr)
            {
                if (n->Walkable)
                {
                    n->Poison = 3;
                }
            }
        }
    }

    void ChainLightningEffect::Use(Actor *source, Actor *target, GameWorld *world)
    {
        // TODO: this is really ugly (and doesn't work)

        std::set<Point> hit;
        bool done = false;

        while (!done && hit.size() < 3)
        {
            if (target != nullptr)
            {
                if (target->Friendly != source->Friendly)
                {
                    // Hit this target with lightning then pick a neighbor
                    target->CombatComp->Damage({5, source}, *world);
                    hit.insert(target->Position);

                    // find a neighbor

                    auto neighbors = world->GetLevel()->GetNeighbors(target->Position.X, target->Position.Y, false);

                    for (auto n : neighbors)
                    {
                        target = world->GetActor(n->X, n->Y);

                        if (target != nullptr)
                        {
                            if (hit.find(target->Position) == hit.end())
                            {
                                break;
                            }
                        }
                    }

                    // no valid neighbors found
                    done = true;
                }
            }
            else
            {
                done = true;
            }
        }
    }

} // namespace cm