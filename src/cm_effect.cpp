#include "cm_effect.h"

#include "cm_actor.h"

namespace cm
{
    void HealEffect::Use(Actor &target)
    {
        target.Heal(Health);
    }
    
} // namespace cm