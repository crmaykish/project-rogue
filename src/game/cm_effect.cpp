#include "cm_effect.h"
#include "cm_actor.h"
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

} // namespace cm