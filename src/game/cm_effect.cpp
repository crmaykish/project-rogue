#include "cm_effect.h"
#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    // Null
    void NullEffect::Use(Actor &target, GameWorld &world)
    {
    }

    std::string NullEffect::GetName()
    {
        return "Null Effect";
    }

    // Damage
    DamageEffect::DamageEffect(int damage) : Damage(damage) {}

    void DamageEffect::Use(Actor &target, GameWorld &world)
    {
        target.HP -= Damage;

        if (target.HP <= 0)
        {
            target.HP = 0;

            if (!target.Friendly)
            {
                target.Active = false;
            }
        }

        world.AddCombatText(CombatText{
            std::to_string(Damage),
            target.TileX,
            target.TileY,
            ColorRed,
            0});
    }

    std::string DamageEffect::GetName()
    {
        return "Damage";
    }

    // Heal
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor &target, GameWorld &world)
    {
        target.HP += Health;

        if (target.HP > target.MaxHP)
        {
            target.HP = target.MaxHP;
        }

        world.AddCombatText(CombatText{
            std::to_string(Health),
            target.TileX,
            target.TileY,
            ColorGreen,
            0});
    }

    std::string HealEffect::GetName()
    {
        return "Healing";
    }

    // Torch Fuel
    void AddTorchFuelEffect::Use(Actor &target, GameWorld &world)
    {
        if (target.Friendly)
        {
            target.TorchFuel += 10;
        }
    }

    std::string AddTorchFuelEffect::GetName()
    {
        return "Torch Light";
    }

    // Random Potions
    void RandomPotionSpawnEffect::Use(Actor &target, GameWorld &world)
    {
        int percentChance = 10; // TODO: make this a parameter

        auto inv = target.GetInventory();

        if (inv != nullptr)
        {
            if (RandomInt(100) < percentChance)
            {
                inv->AddItem(RandomConsumable());
            }
        }
    }

    std::string RandomPotionSpawnEffect::GetName()
    {
        return "Many Potions";
    }

    void LifeStealEffect::Use(Actor &target, GameWorld &world)
    {
        int life = 2;

        auto targetOfTarget = world.GetActor(target.TargetX, target.TargetY);

        if (targetOfTarget == nullptr)
        {
            return;
        }

        // damage the target of target
        // TODO: can't steal more life than target of target has
        auto damage = DamageEffect(life);
        damage.Use(*targetOfTarget, world);

        // heal the target
        auto heal = HealEffect(life);
        heal.Use(target, world);
    }

    std::string LifeStealEffect::GetName()
    {
        return "Life Steal";
    }

    // Experience
    ExperienceEffect::ExperienceEffect(int exp) : Experience(exp) {}

    void ExperienceEffect::Use(Actor &target, GameWorld &world)
    {
        target.Experience += Experience;

        world.AddCombatText(CombatText{
                std::to_string(Experience),
                target.TileX,
                target.TileY,
                ColorBlue,
                0});

        if (target.Experience >= (target.Level * 1000))
        {
            // Scale health pool
            target.MaxHP *= 1.5;
            target.HP = target.MaxHP;

            // Scale mana pool
            target.MaxMana *= 1.4;
            target.Mana = target.MaxMana;

            // Reset experience counter
            Experience -= (target.Level * 1000);

            // Level up
            target.Level++;

            world.AddCombatText(CombatText{
                "Level Up!",
                target.TileX,
                target.TileY,
                ColorBlue,
                0});
        }
    }

    std::string ExperienceEffect::GetName()
    {
        return "Experience";
    }

} // namespace cm