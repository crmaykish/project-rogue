#include "cm_effect.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_item.h"
#include "cm_random.h"
#include "cm_logger.h"
#include "cm_abilities.h"

namespace cm
{
    // Damage
    DamageEffect::DamageEffect(int damage) : Damage(damage) {}

    void DamageEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.Stats.AdjustHP(-Damage);

        if (actor.Stats.HP() == 0)
        {
            if (!actor.Friendly)
            {
                actor.Active = false;
            }
        }

        world.AddCombatText(CombatText{
            std::to_string(Damage),
            actor.Position.X,
            actor.Position.Y,
            ColorRed,
            0});
    }

    // Damage Target
    DamageTargetEffect::DamageTargetEffect(int damage) : Damage(damage) {}

    void DamageTargetEffect::Use(Actor &actor, GameWorld &world)
    {
        auto target = world.GetActor(actor.Target.X, actor.Target.Y);

        if (target != nullptr)
        {
            auto damage = DamageEffect(Damage);
            damage.Use(*target, world);
        }
    }

    // Heal
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.Stats.AdjustEnergy(Health);

        world.AddCombatText(CombatText{
            std::to_string(Health),
            actor.Position.X,
            actor.Position.Y,
            ColorGreen,
            0});
    }

    // Energy
    EnergyEffect::EnergyEffect(int energy) : Energy(energy) {}

    void EnergyEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.Stats.AdjustEnergy(Energy);

        world.AddCombatText(CombatText{
            std::to_string(Energy),
            actor.Position.X,
            actor.Position.Y,
            ColorBlue,
            0});
    }

    // Energy
    RejuvEffect::RejuvEffect(int health, int energy) : Health(health), Energy(energy) {}

    void RejuvEffect::Use(Actor &actor, GameWorld &world)
    {
        auto hp = HealEffect(Health);
        auto mp = EnergyEffect(Energy);

        hp.Use(actor, world);
        mp.Use(actor, world);
    }

    // Torch Fuel
    void AddTorchFuelEffect::Use(Actor &actor, GameWorld &world)
    {
        if (actor.Friendly)
        {
            actor.TorchFuel += 10;
        }
    }

    // Random Potions
    void RandomConsumableEffect::Use(Actor &actor, GameWorld &world)
    {
        auto inv = actor.GetInventory();

        if (inv != nullptr)
        {
            inv->AddItem(RandomConsumable());
        }
    }

    void LifeStealEffect::Use(Actor &actor, GameWorld &world)
    {
        int life = 2;

        auto targetOfTarget = world.GetActor(actor.Target.X, actor.Target.Y);

        if (targetOfTarget == nullptr)
        {
            return;
        }

        // damage the actor's of target
        // TODO: can't steal more life than target of target has
        auto damage = DamageEffect(life);
        damage.Use(*targetOfTarget, world);

        // heal the actor
        auto heal = HealEffect(life);
        heal.Use(actor, world);
    }

    // Experience
    ExperienceEffect::ExperienceEffect(int exp) : Experience(exp) {}

    void ExperienceEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.Experience += Experience;

        world.AddCombatText(CombatText{
            std::to_string(Experience),
            actor.Position.X,
            actor.Position.Y,
            ColorPurple,
            0});

        if (actor.Experience >= (actor.Level * 1000))
        {
            // Level up
            actor.Level++;

            // Reset experience counter
            Experience -= (actor.Level * 1000);

            world.AddCombatText(CombatText{
                "Level Up!",
                actor.Position.X,
                actor.Position.Y,
                ColorBlue,
                0});
        }
    }

    LearnAbilityEffect::LearnAbilityEffect(std::unique_ptr<Ability> learnAbility)
        : LearnAbility(std::move(learnAbility)) {}

    void LearnAbilityEffect::Use(Actor &actor, GameWorld &world)
    {

        auto abilitySet = actor.GetAbilitySet();

        int freeSlot = 0;

        // while loop, moron
        for (int i = 0; i < 4; i++)
        {
            if (abilitySet->AbilityAt(freeSlot) != nullptr)
            {
                freeSlot++;
            }
            else
            {
                break;
            }
        }

        abilitySet->SetAbility(freeSlot, std::move(LearnAbility));
    }

} // namespace cm