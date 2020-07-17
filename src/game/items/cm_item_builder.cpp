#include "cm_item_builder.h"
#include "cm_random.h"

namespace cm
{
    struct ItemAsset
    {
        AssetKey key;
        std::vector<std::string> names;
    };

    struct ItemBuilder
    {
        std::vector<ItemAsset> assets;

        std::vector<ActorStatType> statModTypes;
        int minStatMods;
        int maxStatMods;

        std::vector<ItemModifier (*)()> itemModTypes;
        int minItemMods;
        int maxItemMods;
    };

    ItemAsset SwordAsset = {
        AssetKey::SwordGreyTexture,
        {"Sword", "Short Sword", "Long Sword", "Heavy Sword"},
    };

    ItemAsset AxeAsset = {
        AssetKey::AxeTexture,
        {"Hatchet", "Axe", "Heavy Axe", "Broad Axe"},
    };

    auto AllStatModTypes = {
        ActorStatType::MaxHealth,
        ActorStatType::MaxEnergy,
        ActorStatType::Vitality,
        ActorStatType::Strength,
        ActorStatType::Dexterity,
        ActorStatType::Intellect,
    };

    auto AllItemModifiers = {
        &ItemModifierExtraHit,
        &ItemModifierLifeLeech,
        &ItemModifierSacrifice,
    };

    ItemBuilder WeaponBuilder = {
        .assets = {SwordAsset, AxeAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 4,
        .itemModTypes = AllItemModifiers,
        .minItemMods = 0,
        .maxItemMods = 2,
    };

    std::unordered_map<ItemType, ItemBuilder> ItemBuilders = {
        {ItemType::OneHand, WeaponBuilder},
    };

    std::unique_ptr<Item> BuildItem()
    {
        // Randomize type
        return BuildItem(ItemType::OneHand);
    }

    std::unique_ptr<Item> BuildItem(ItemType type)
    {
        auto builder = ItemBuilders.at(type);
        auto asset = builder.assets.at(RandomInt(builder.assets.size()));

        // Create the base item
        auto item = std::make_unique<Item>();
        item->Type = type;
        item->Name = asset.names.at(RandomInt(asset.names.size()));
        item->TextureKey = asset.key;

        // Add stat modifiers
        for (int i = 0; i < RandomInt(builder.minStatMods, builder.maxStatMods); i++)
        {
            // TODO: don't repeat modifiers
            // TODO: multiplier mods
            // TODO: define value ranges in the builder
            auto statMod = builder.statModTypes.at(RandomInt(builder.statModTypes.size()));
            auto value = RandomInt(1, 10);
            item->AddStatModifier(ActorStatModifier(statMod, value, ActorStatModifierType::Add));
        }

        // Add behavior modifiers
        for (int i = 0; i < RandomInt(builder.minItemMods, builder.maxItemMods); i++)
        {
            // TODO: don't repeat modifiers
            // TODO: define triggers in the builder
            auto itemMod = builder.itemModTypes.at(RandomInt(builder.itemModTypes.size()));
            item->AddModifier(ItemModifierTrigger::Attack, itemMod());
        }

        return item;
    }
} // namespace cm