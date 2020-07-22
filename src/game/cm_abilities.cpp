#include "cm_abilities.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_logger.h"
#include "cm_effect.h"
#include "cm_random.h"

namespace cm
{
    // AbilitySet

    void AbilitySet::SetAbility(int slot, std::unique_ptr<Ability> ability)
    {
        if (slot >= 0 && slot < Abilities.size())
        {
            Abilities[slot] = std::move(ability);
        }
    }

    Ability *AbilitySet::AbilityAt(int slot)
    {
        if (slot < 0 || slot >= 4)
        {
            return nullptr;
        }

        return Abilities.at(slot).get();
    }

    bool AbilitySet::AbilityReady(int slot)
    {
        return false;
    }

    void AbilitySet::Reset()
    {
        std::fill(Abilities.begin(), Abilities.end(), nullptr);
    }

    int AbilitySet::FreeSlot()
    {
        int freeSlot = -1;

        for (auto i = 0; i < Abilities.size(); i++)
        {
            if (Abilities.at(i) == nullptr)
            {
                freeSlot = i;
                break;
            }
        }

        return freeSlot;
    }

    bool AttackAbility::Use(Actor &user, GameWorld &world)
    {
        auto target = world.GetActor(user.Target.X, user.Target.Y);

        // TODO range checking

        if (target == nullptr)
        {
            return false;
        }

        if (Distance(user.Position, target->Position) > 1)
        {
            return false;
        }

        // TODO: consider target's defense rating
        auto baseDamage = user.Stats.GetAttackRating() / 4;
        int actualDamage = RandomInt(baseDamage / 2, baseDamage * 1.25);

        // Damage the target
        target->CombatComp->Damage({actualDamage, &user}, world);

        return true;
    }

    bool HealAbility::Use(Actor &user, GameWorld &world)
    {
        user.CombatComp->Heal({user.Stats.MaxHP() * 0.4, &user}, world);

        return true;
    }

    bool CleaveAbility::Use(Actor &user, GameWorld &world)
    {
        // Damage all targets within one tile of the user
        auto neighbors = world.GetLevel()->GetNeighbors(user.Position.X, user.Position.Y);

        for (auto n : neighbors)
        {
            auto enemy = world.GetActor(n->X, n->Y);

            if (enemy != nullptr && !enemy->Friendly)
            {
                // TODO: consider target's defense rating
                auto baseDamage = user.Stats.GetAttackRating() / 5;
                int actualDamage = RandomInt(baseDamage / 2, baseDamage);
                // auto effect = DamageEffect({actualDamage, &user});
                // effect.Use(*enemy, world);

                user.Target = enemy->Position;
            }
        }

        return true;
    }

    std::unique_ptr<Ability> RandomAbility()
    {
        int r = RandomInt(2);

        if (r == 0)
            return std::make_unique<HealAbility>();
        else if (r == 1)
            return std::make_unique<CleaveAbility>();

        return nullptr;
    }

} // namespace cm