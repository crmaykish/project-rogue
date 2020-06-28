#include "cm_potion.h"

#include "cm_effect.h"

namespace cm
{
    HealthPotion::HealthPotion()
    {
        AddUseEffect(std::make_shared<HealEffect>());
    }

    std::string HealthPotion::GetName()
    {
        return "Health Potion";
    }

} // namespace cm