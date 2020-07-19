#include "cm_item_modifier.h"
#include "cm_abilities.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    ItemModifier ItemModifierHeal()
    {
        return ItemModifier{"Health",
                            std::make_unique<HealEffect>(20),
                            100};
    }

    ItemModifier ItemModifierMana()
    {
        return ItemModifier{"Energy",
                            std::make_unique<EnergyEffect>(3),
                            100};
    }

    ItemModifier ItemModifierRejuv()
    {
        return ItemModifier{"Rejuvenation",
                            std::make_unique<RejuvEffect>(10, 2),
                            100};
    }

    ItemModifier ItemModifierLearnAbility()
    {
        // TODO: pass in random ability

        return ItemModifier{"Skill",
                            std::make_unique<LearnAbilityEffect>(
                                std::make_unique<CleaveAbility>()),
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