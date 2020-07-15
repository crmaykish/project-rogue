#include "cm_effect.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_item.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    // Damage
    DamageEffect::DamageEffect(int damage) : Damage(damage) {}

    void DamageEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.HP -= Damage;

        if (actor.HP <= 0)
        {
            actor.HP = 0;

            if (!actor.Friendly)
            {
                actor.Active = false;
            }
        }

        world.AddCombatText(CombatText{
            std::to_string(Damage),
            actor.TileX,
            actor.TileY,
            ColorRed,
            0});
    }

    // Damage Target
    DamageTargetEffect::DamageTargetEffect(int damage) : Damage(damage) {}

    void DamageTargetEffect::Use(Actor &actor, GameWorld &world)
    {
        auto target = world.GetActor(actor.TargetX, actor.TargetY);

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
        actor.HP += Health;

        if (actor.HP > actor.MaxHP)
        {
            actor.HP = actor.MaxHP;
        }

        world.AddCombatText(CombatText{
            std::to_string(Health),
            actor.TileX,
            actor.TileY,
            ColorGreen,
            0});
    }

    // Mana
    ManaEffect::ManaEffect(int mana) : Mana(mana) {}

    void ManaEffect::Use(Actor &actor, GameWorld &world)
    {
        actor.Mana += Mana;

        if (actor.Mana > actor.MaxMana)
        {
            actor.Mana = actor.MaxMana;
        }

        world.AddCombatText(CombatText{
            std::to_string(Mana),
            actor.TileX,
            actor.TileY,
            ColorBlue,
            0});
    }

    // Mana
    RejuvEffect::RejuvEffect(int health, int mana) : Health(health), Mana(mana) {}

    void RejuvEffect::Use(Actor &actor, GameWorld &world)
    {
        auto hp = HealEffect(Health);
        auto mp = ManaEffect(Mana);

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

        auto targetOfTarget = world.GetActor(actor.TargetX, actor.TargetY);

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
            actor.TileX,
            actor.TileY,
            ColorPurple,
            0});

        if (actor.Experience >= (actor.Level * 1000))
        {
            // Scale health pool
            actor.MaxHP *= 1.5;
            actor.HP = actor.MaxHP;

            // Scale mana pool
            actor.MaxMana *= 1.4;
            actor.Mana = actor.MaxMana;

            // Reset experience counter
            Experience -= (actor.Level * 1000);

            // Level up
            actor.Level++;

            world.AddCombatText(CombatText{
                "Level Up!",
                actor.TileX,
                actor.TileY,
                ColorBlue,
                0});
        }
    }

} // namespace cm