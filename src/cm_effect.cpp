#include "cm_effect.h"

#include "cm_actor.h"

namespace cm
{
    Effect::~Effect() {}

    void HealEffect::Use(Actor &target)
    {
        target.Heal(Health);
    }
    
} // namespace cm