#include "cm_item_builder.h"
#include "cm_random.h"

namespace cm
{
    struct ItemAsset
    {
        // TODO: Make this a vector of possible assets
        AssetKey key;
        // TODO: these names should indicate the item level
        std::vector<std::string> names;
    };

    struct ItemBuilder
    {
        std::vector<ItemAsset> assets;

        std::vector<ActorStatType> statModTypes;
        int minStatMods = 0;
        int maxStatMods = 0;

        std::vector<ItemModifier (*)()> itemModTypes;
        std::vector<ItemModifierTrigger> itemModTriggers;
        int minItemMods = 0;
        int maxItemMods = 0;
    };

    ItemAsset SwordAsset = {
        AssetKey::SwordGreyTexture,
        {"Sword", "Short Sword", "Long Sword", "Heavy Sword"},
    };

    ItemAsset AxeAsset = {
        AssetKey::AxeTexture,
        {"Hatchet", "Axe", "Heavy Axe", "Broad Axe"},
    };

    ItemAsset HelmetLeatherAsset = {
        AssetKey::HelmetLeatherTexture,
        {"Hood", "Cowl", "Coif"},
    };

    ItemAsset HelmetSteelAsset = {
        AssetKey::HelmetSteelTexture,
        {"Cap", "Helm"},
    };

        ItemAsset BookAsset = {
        AssetKey::BookBlueTexture,
        {"Text", "Book", "Manual", "Tome"},
    };

    ItemAsset PotionAsset = {
        AssetKey::HealthPotionTexture,
        {"Potion", "Phial", "Flask", "Decanter"},
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
        &ItemModifierExplosion,
    };

    ItemBuilder WeaponBuilder = {
        .assets = {SwordAsset, AxeAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 2,
        .itemModTypes = AllItemModifiers,
        .itemModTriggers = {ItemModifierTrigger::Attack},
        .minItemMods = 0,
        .maxItemMods = 1,
    };

    ItemBuilder HelmetBuilder = {
        .assets = {HelmetLeatherAsset, HelmetSteelAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 3,
        .itemModTypes = {
            &ItemModifierExplosion,
        },
        .itemModTriggers = {ItemModifierTrigger::Defend},
        .minItemMods = 1,
        .maxItemMods = 1,
    };

    ItemBuilder PotionBuilder = {
        .assets = {PotionAsset},
        .statModTypes = {},
        .minStatMods = 0,
        .maxStatMods = 0,
        .itemModTypes = {
            &ItemModifierHeal,
            &ItemModifierMana,
            &ItemModifierRejuv,
        },
        .itemModTriggers = {ItemModifierTrigger::Use},
        .minItemMods = 1,
        .maxItemMods = 1,
    };

    std::unordered_map<ItemType, ItemBuilder>
        ItemBuilders = {
            {ItemType::OneHand, WeaponBuilder},
            {ItemType::Consumable, PotionBuilder},
            {ItemType::Head, HelmetBuilder},
    };

    std::unique_ptr<Item> BuildItem()
    {
        switch (RandomInt(3))
        {
        case 0:
            return BuildItem(ItemType::Consumable);
            break;
        case 1:
            return BuildItem(ItemType::OneHand);
            break;
        case 2:
            return BuildItem(ItemType::Head);
            break;
        default:
            return nullptr;
            break;
        }
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

        // Consumables need charges
        if (type == ItemType::Consumable)
        {
            item->LimitedCharge = true;
            item->Charges = 1;
        }

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
            auto triggerType = builder.itemModTriggers.at(RandomInt(builder.itemModTriggers.size()));
            item->AddModifier(triggerType, itemMod());
        }

        return item;
    }
} // namespace cm