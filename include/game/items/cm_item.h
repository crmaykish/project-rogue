#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "cm_assets.h"
#include "cm_actor_stat.h"
#include "cm_effect.h"

namespace cm
{
    enum struct ItemType
    {
        Consumable,
        Head,
        Chest,
        Boots,
        OneHand,
        OffHand,
    };

    // TODO: Item stat modifiers, e.g. extra base damage/armor

    struct Item
    {
        // Details
        std::string Name;
        std::string Description;
        ItemType Type = ItemType::Consumable;
        AssetKey TextureKey;

        // Flags
        bool PickedUp = false;
        bool LimitedCharge = false;
        int Charges = 0;

        // Modifiers
        std::vector<ActorStatModifier> StatModifiers;
        EffectMap Effects;

        // Methods
        std::string DisplayName();
    };

} // namespace cm

#endif // CM_ITEM_H
