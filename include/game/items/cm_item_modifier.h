#ifndef CM_ITEM_MODIFIER_H
#define CM_ITEM_MODIFIER_H

#include <memory>
#include <string>
#include "cm_effect.h"

namespace cm
{
    class Item;

    enum struct ItemModifierTrigger
    {
        Any,    /**< Triggered when the owner makes any action */
        Use,    /**< Triggered when the actor activates the item from inventory */
        Attack, /**< Triggered when the owner attacks */
        Defend, /**< Triggered when the owner receives damage */
        Kill,   /**< Triggered when owner kills another actor */
    };

    struct ItemModifier
    {
        std::string Name;
        std::unique_ptr<Effect> MainEffect;
        int PercentChance = 100;
    };

    ItemModifier ItemModifierHeal();
    ItemModifier ItemModifierMana();
    ItemModifier ItemModifierRejuv();

    ItemModifier ItemModifierLifeLeech();
    ItemModifier ItemModifierExtraHit();
    ItemModifier ItemModifierSacrifice();

} // namespace cm

#endif /* CM_ITEM_MODIFIER_H */
