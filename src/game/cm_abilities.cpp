#include "cm_abilities.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_logger.h"
#include "cm_effect.h"

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
        // TODO: range checking

        auto target = world.GetActor(TargetX, TargetY);

        if (target == nullptr)
        {
            return false;
        }

        auto effect = DamageEffect(user.GetAttack());
        effect.Use(*target);

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
        // TODO: range checking
        auto target = world.GetActor(TargetX, TargetY);

        if (target == nullptr)
        {
            return false;
        }

        auto effect = DamageEffect(user.GetAttack());
        effect.Use(*target);

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
        int manaCost = 20;

        if (user.Mana < manaCost || user.HP == user.MaxHP)
        {
            return false;
        }

        user.Mana -= manaCost;

        auto effect = HealEffect(user.MaxHP * 0.4);

        effect.Use(user);

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
        // do damage to everything around the user

        auto neighbors = world.GetLevel()->GetNeighbors(user.TileX, user.TileY);

        for (auto n : neighbors)
        {
            auto enemy = world.GetActor(n->X, n->Y);

            if (enemy != nullptr && !enemy->Friendly)
            {
                // TODO: wrap up actors taking damage in an Effect

                // TODO: scale with weapon damage
                enemy->HP -= 12;

                if (enemy->HP <= 0)
                {
                    enemy->HP = 0;
                    enemy->Active = false;
                }
            }
        }

        return true;
    }

} // namespace cm