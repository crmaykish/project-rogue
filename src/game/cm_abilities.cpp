#include <algorithm>
#include <set>
#include "cm_abilities.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_logger.h"
#include "cm_effect.h"
#include "cm_random.h"
#include "cm_enemy.h"

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
        auto target = world.GetActor(user.Target);

        if (target == nullptr)
        {
            return false;
        }

        auto attackRange = 1;

        // If the actor has a weaponed equipped, use its range
        auto weapon = user.InventoryComp->EquipmentAt(ItemType::OneHand);

        if (weapon != nullptr)
        {
            attackRange = weapon->Range;
        }

        auto distance = Distance(user.Position, target->Position);

        if (distance > attackRange)
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
        user.CombatComp->Heal({static_cast<int>(user.Stats.MaxHP() * 0.4), &user}, world);

        return true;
    }

    bool CleaveAbility::Use(Actor &user, GameWorld &world)
    {
        // Damage all targets within one tile of the user
        auto neighbors = world.GetLevel()->GetNeighbors(user.Position);

        for (auto n : neighbors)
        {
            auto enemy = world.GetActor(n->Position);

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

    bool TeleportAbility::Use(Actor &user, GameWorld &world)
    {
        auto tile = world.GetLevel()->GetTile(user.Target);

        if (world.GetActor(tile->Position) != nullptr)
        {
            return false;
        }

        if (Distance(user.Position, tile->Position) > 4)
        {
            return false;
        }

        if (tile->Walkable)
        {
            user.Position = tile->Position;
        }

        return true;
    }

    bool SlimeSplitAbility::Use(Actor &user, GameWorld &world)
    {
        auto neighbors = world.GetLevel()->GetNeighbors(user.Position);

        if (!neighbors.empty())
        {
            std::random_shuffle(neighbors.begin(), neighbors.end());

            for (auto n : neighbors)
            {
                if (n->Walkable && world.GetActor(n->Position) == nullptr)
                {
                    auto currentHP = user.Stats.HP();

                    // Adjust the original slime's max HP to its current HP
                    user.Stats.SetStatBaseValue(ActorStatType::MaxHealth, currentHP);

                    // Create a new slime with the same max HP
                    auto clone = std::make_unique<Slime>(n->Position);
                    clone->Stats.SetStatBaseValue(ActorStatType::Health, currentHP);
                    clone->Stats.SetStatBaseValue(ActorStatType::MaxHealth, currentHP);
                    world.AddEnemy(std::move(clone));

                    return true;
                }
            }
        }

        return false;
    }

    bool PoisonAuraAbility::Use(Actor &user, GameWorld &world)
    {
        auto effect = PoisonAuraEffect();
        effect.Use(&user, nullptr, &world);

        return true;
    }

    bool ChainLightningAbility::Use(Actor &user, GameWorld &world)
    {
        auto target = world.GetActor(user.Target);

        if (target == nullptr)
        {
            return false;
        }

        auto effect = ChainLightningEffect();
        effect.Use(&user, target, &world);

        return true;
    }

    std::unique_ptr<Ability> RandomAbility()
    {
        int r = RandomInt(5);

        if (r == 0)
            return std::make_unique<HealAbility>();
        else if (r == 1)
            return std::make_unique<CleaveAbility>();
        else if (r == 2)
            return std::make_unique<TeleportAbility>();
        else if (r == 3)
            return std::make_unique<PoisonAuraAbility>();
        else if (r == 4)
            return std::make_unique<ChainLightningAbility>();

        return nullptr;
    }

} // namespace cm