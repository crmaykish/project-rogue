#include "cm_item_modifier.h"

namespace cm
{
    ItemModifier ItemModifierHeal()
    {
        return ItemModifier{"Health",
                            std::make_unique<HealEffect>(50),
                            100};
    }

    ItemModifier ItemModifierMana()
    {
        return ItemModifier{"Mana",
                            std::make_unique<ManaEffect>(60),
                            100};
    }

    ItemModifier ItemModifierRejuv()
    {
        return ItemModifier{"Rejuvenation",
                            std::make_unique<RejuvEffect>(40, 40),
                            100};
    }

    ItemModifier ItemModifierLifeLeech()
    {
        return ItemModifier{"The Leech",
                            std::make_unique<LifeStealEffect>(),
                            100};
    }

    ItemModifier ItemModifierExtraHit()
    {
        return ItemModifier{"Persistence",
                            std::make_unique<DamageTargetEffect>(10),
                            50};
    }

    ItemModifier ItemModifierSacrifice()
    {
        return ItemModifier{"Sacrifice",
                            std::make_unique<DamageEffect>(5),
                            25};
    }

} // namespace cm