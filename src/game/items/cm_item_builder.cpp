#include <set>
#include "cm_item_builder.h"
#include "cm_random.h"

namespace cm
{
    // TODO: better way to organize these effects
    std::shared_ptr<Effect> RandomAttackEffect();
    std::shared_ptr<Effect> RandomDefendEffect();
    std::shared_ptr<Effect> RandomUseEffect();

    // Builder Structures

    struct ItemAsset
    {
        AssetKey key;
        std::vector<std::string> names;
    };

    struct ItemBuilder
    {
        std::vector<ItemAsset> assets;
        std::vector<ActorStatType> statModTypes;
        int minStatMods = 0;
        int maxStatMods = 0;
        bool onAttackModifiers = false;
        bool onDefenseModifiers = false;
        bool onUseModifiers = false;
    };

    // Asset Definitions

    // Weapons
    ItemAsset DaggerAsset = {AssetKey::DaggerTexture, {"Dagger"}};
    ItemAsset SwordAsset = {AssetKey::SwordGreyTexture, {"Sword"}};
    ItemAsset AxeAsset = {AssetKey::AxeTexture, {"Axe"}};
    ItemAsset HammerAsset = {AssetKey::HammerTexture, {"Hammer"}};
    ItemAsset BowAsset = {AssetKey::BowTexture, {"Bow"}};
    ItemAsset WandAsset = {AssetKey::WandBlueTexture, {"Wand"}};

    // Armor
    ItemAsset HelmetLeatherAsset = {AssetKey::HelmetLeatherTexture, {"Hood"}};
    ItemAsset HelmetSteelAsset = {AssetKey::HelmetSteelTexture, {"Helm"}};
    ItemAsset BootsLeatherAsset = {AssetKey::BootsLeatherTexture, {"Boots"}};

    // Offhand
    ItemAsset BucklerAsset = {AssetKey::BucklerTexture, {"Buckler"}};
    ItemAsset ShieldAsset = {AssetKey::ShieldTowerTexture, {"Shield"}};

    // Consumables
    ItemAsset BookAsset = {AssetKey::BookBlueTexture, {"Book"}};
    ItemAsset PotionAsset = {AssetKey::RejuvPotionTexture, {"Potion"}};

    // Stat Modifier Collections

    auto AllStatModTypes = {
        ActorStatType::MaxHealth,
        // ActorStatType::MaxEnergy,
        ActorStatType::Vitality,
        ActorStatType::Strength,
        ActorStatType::Dexterity,
        ActorStatType::Intellect,
    };

    // Item Builder Instances

    ItemBuilder WeaponBuilder = {
        .assets = {DaggerAsset, SwordAsset, AxeAsset, HammerAsset, WandAsset, BowAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 1,
        .onAttackModifiers = true,
    };

    ItemBuilder HelmetBuilder = {
        .assets = {HelmetLeatherAsset, HelmetSteelAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 1,
        .onDefenseModifiers = true,
    };

    ItemBuilder BootsBuilder = {
        .assets = {BootsLeatherAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 1,
        .onDefenseModifiers = true,
    };

    ItemBuilder OffhandBuilder = {
        .assets = {BucklerAsset, ShieldAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 1,
        .onAttackModifiers = true,
        .onDefenseModifiers = true,
    };

    ItemBuilder PotionBuilder = {
        .assets = {PotionAsset},
        .statModTypes = {},
        .minStatMods = 0,
        .maxStatMods = 0,
        .onUseModifiers = true,
    };

    // Item Building Implementation

    std::unordered_map<ItemType, ItemBuilder>
        ItemBuilders = {
            {ItemType::OneHand, WeaponBuilder},
            {ItemType::Head, HelmetBuilder},
            {ItemType::Boots, BootsBuilder},
            {ItemType::OffHand, OffhandBuilder},
            {ItemType::Consumable, PotionBuilder},

    };

    std::unique_ptr<Item> BuildItem()
    {
        switch (RandomInt(5))
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
        case 3:
            return BuildItem(ItemType::Boots);
            break;
        case 4:
            return BuildItem(ItemType::OffHand);
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

        std::set<ActorStatType> usedMods;

        // Add stat modifiers
        for (int i = 0; i < RandomInt(builder.minStatMods, builder.maxStatMods); i++)
        {
            auto statMod = builder.statModTypes.at(RandomInt(builder.statModTypes.size()));

            while (usedMods.find(statMod) != usedMods.end())
            {
                statMod = builder.statModTypes.at(RandomInt(builder.statModTypes.size()));
            }

            // TODO: define value ranges in the builder
            auto value = RandomInt(1, 5);
            // TODO: multiplier mods
            item->StatModifiers.emplace_back(ActorStatModifier(statMod, value, ActorStatModifierType::Add));

            usedMods.insert(statMod);
        }

        // TODO: for now, items can only have one effect of each trigger type

        if (builder.onAttackModifiers)
        {
            if (RandomPercentCheck(10))
            {
                item->Effects.Add(EffectTrigger::Attack, RandomAttackEffect());
            }
        }

        if (builder.onDefenseModifiers)
        {
            if (RandomPercentCheck(10))
            {
                item->Effects.Add(EffectTrigger::Defend, RandomDefendEffect());
            }
        }
        if (builder.onUseModifiers)
        {
            // Note: on-use effects are 100% chance
            item->Effects.Add(EffectTrigger::UseItem, RandomUseEffect());
        }

        return item;
    }

    std::shared_ptr<Effect> RandomAttackEffect()
    {
        auto r = RandomInt(4);

        if (r == 0)
            return std::make_shared<ExplosionEffect>();
        else if (r == 1)
            return std::make_shared<LifeStealEffect>();
        else if (r == 2)
            return std::make_shared<HealEffect>();
        else if (r == 3)
            return std::make_shared<SacrificeEffect>();
        else
            return nullptr;
    }

    std::shared_ptr<Effect> RandomDefendEffect()
    {
        auto r = RandomInt(3);

        if (r == 0)
            return std::make_shared<RetaliationEffect>();
        else if (r == 1)
            return std::make_shared<ExplosionEffect>();
        else if (r == 2)
            return std::make_shared<HealEffect>();
        else
            return nullptr;
    }

    std::shared_ptr<Effect> RandomUseEffect()
    {
        auto r = RandomInt(3);

        if (r == 0)
            return std::make_shared<HealEffect>();
        else if (r == 1)
            return std::make_shared<ExplosionEffect>();
        else if (r == 2)
            return std::make_shared<SacrificeEffect>();
        else
            return nullptr;
    }

} // namespace cm