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

    // TODO: is this function even necessary?
    bool AbilitySet::UseAbility(int slot, Actor &user, GameWorld &world)
    {
        Abilities.at(slot)->Use(user, world);

        return true;
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

    // Melee

    std::string MeleeAbility::GetName()
    {
        return "Attack";
    }

    std::string MeleeAbility::GetDescription()
    {
        return "Perform a basic melee attack";
    }

    AssetKey MeleeAbility::GetIcon()
    {
        return AssetKey::MeleeIcon;
    }

    bool MeleeAbility::Use(Actor &user, GameWorld &world)
    {
        auto target = world.GetActor(user.Target.X, user.Target.Y);

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
        auto effect = DamageEffect(actualDamage);
        effect.Use(*target, world);

        return true;
    }

    // Ranged

    std::string RangedAbility::GetName()
    {
        return "Shoot";
    }

    std::string RangedAbility::GetDescription()
    {
        return "Perform a basic attack with a ranged weapon";
    }

    AssetKey RangedAbility::GetIcon()
    {
        return AssetKey::RangeIcon;
    }

    bool RangedAbility::Use(Actor &user, GameWorld &world)
    {
        auto target = world.GetActor(user.Target.X, user.Target.Y);

        if (target == nullptr)
        {
            return false;
        }

        if (Distance(user.Position, target->Position) > 4)
        {
            return false;
        }

        // TODO: consider target's defense rating
        auto baseDamage = user.Stats.GetAttackRating() / 4;
        int actualDamage = RandomInt(baseDamage / 2, baseDamage * 1.25);
        auto effect = DamageEffect(actualDamage);
        effect.Use(*target, world);

        return true;
    }

    // Heal

    std::string HealAbility::GetName()
    {
        return "Heal";
    }

    std::string HealAbility::GetDescription()
    {
        return "Heals the caster for 40% HP";
    }

    AssetKey HealAbility::GetIcon()
    {
        return AssetKey::HealIcon;
    }

    bool HealAbility::Use(Actor &user, GameWorld &world)
    {
        auto effect = HealEffect(user.Stats.MaxHP() * 0.4);

        effect.Use(user, world);

        return true;
    }

    // Cleave

    std::string CleaveAbility::GetName()
    {
        return "Cleave";
    }

    std::string CleaveAbility::GetDescription()
    {
        return "Hit all enemies within 1 tile";
    }

    AssetKey CleaveAbility::GetIcon()
    {
        return AssetKey::CleaveIcon;
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
                auto effect = DamageEffect(actualDamage);
                effect.Use(*enemy, world);

                user.Target = enemy->Position;
            }
        }

        return true;
    }

} // namespace cm