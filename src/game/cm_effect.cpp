#include "cm_effect.h"
#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    // Damage
    DamageEffect::DamageEffect(int damage) : Damage(damage) {}

    void DamageEffect::Use(Actor &target)
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

    // Heal
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor &target)
    {
        Log("healing for: " + std::to_string(Health), LOG_INFO);

        target.HP += Health;

        if (target.HP > target.MaxHP)
        {
            target.HP = target.MaxHP;
        }
    }

    // Torch Fuel
    void AddTorchFuelEffect::Use(Actor &target)
    {
        if (target.Friendly)
        {
            target.TorchFuel += 10;
        }
    }

} // namespace cm