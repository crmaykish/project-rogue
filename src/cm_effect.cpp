#include "cm_effect.h"

#include "cm_actor.h"

namespace cm
{
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor &target)
    {
        target.Heal(Health);
    }

} // namespace cm