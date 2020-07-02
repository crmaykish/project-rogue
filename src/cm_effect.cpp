#include "cm_effect.h"

#include "cm_actor.h"

namespace cm
{
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor &target)
    {
        target.HP += Health;

        if (target.HP > target.MaxHP)
        {
            target.HP = target.MaxHP;
        }
    }

    void AddTorchFuelEffect::Use(Actor &target)
    {
        if (target.Friendly)
        {
            target.TorchFuel += 10;
        }
    }

} // namespace cm