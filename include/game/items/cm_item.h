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

    static std::unordered_map<ActorStatType, std::string> StatNames = {
        {ActorStatType::MaxHealth, "HP"},
        {ActorStatType::MaxEnergy, "NRG"},
        {ActorStatType::Vitality, "VIT"},
        {ActorStatType::Strength, "STR"},
        {ActorStatType::Dexterity, "AGI"},
        {ActorStatType::Intellect, "INT"},
    };

    static std::unordered_map<ActorStatType, std::string> StatPrefixes = {
        {ActorStatType::MaxHealth, "Healthy"},
        {ActorStatType::MaxEnergy, "Energetic"},
        {ActorStatType::Vitality, "Vigorous"},
        {ActorStatType::Strength, "Strong"},
        {ActorStatType::Dexterity, "Agile"},
        {ActorStatType::Intellect, "Wise"},
    };

    // TODO: Item stat modifiers, e.g. extra base damage/armor

    struct Item
    {
        // Details
        std::string Name;
        std::string Description;
        ItemType Type = ItemType::Consumable;
        AssetKey TextureKey;
        int Range = 0; // This is only applicable to weapons

        // Flags
        bool PickedUp = false;

        // Modifiers
        std::vector<ActorStatModifier> StatModifiers;
        EffectMap Effects;

        // Methods
        std::string DisplayName();
    };

} // namespace cm

#endif // CM_ITEM_H
