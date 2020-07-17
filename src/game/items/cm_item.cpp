#include "cm_item.h"
#include "cm_random.h"

namespace cm
{
    void Item::Use(ItemModifierTrigger trigger, Actor &owner, GameWorld &world)
    {
        if (LimitedCharge && Charges == 0)
        {
            return;
        }

        if (Modifiers.find(trigger) != Modifiers.end())
        {
            for (auto const &mod : Modifiers.at(trigger))
            {
                if (RandomInt(100) < mod.PercentChance)
                {
                    mod.MainEffect->Use(owner, world);
                }
            }
        }

        Charges--;
    }

    void Item::AddStatModifier(ActorStatModifier statModifier)
    {
        StatModifiers.emplace_back(statModifier);
    }

    void Item::AddModifier(ItemModifierTrigger trigger, ItemModifier modifier)
    {
        if (Modifiers.find(trigger) == Modifiers.end())
        {
            // Vector at this trigger is empty, create it before trying to insert a new modifier
            Modifiers.emplace(trigger, std::vector<ItemModifier>());
        }

        Modifiers.at(trigger).push_back(std::move(modifier));
    }

    std::vector<ActorStatModifier> &Item::GetStatModifiers()
    {
        return StatModifiers;
    }

    AssetKey Item::GetTextureKey()
    {
        return TextureKey;
    }

    std::string Item::DisplayName()
    {
        // TODO: cache this display name once its generated, it will never change
        auto name = Name;

        if (Type == ItemType::Consumable)
        {
            if (Modifiers.find(ItemModifierTrigger::Use) != Modifiers.end())
            {
                for (auto &m : Modifiers.at(ItemModifierTrigger::Use))
                {
                    name = m.Name + " " + name;
                }
            }
        }
        else if (Type == ItemType::OneHand || Type == ItemType::OffHand)
        {
            for (const auto &s : StatModifiers)
            {
                name = StatPrefixes(s.GetStatType()) + " " + name;
            }

            if (Modifiers.find(ItemModifierTrigger::Attack) != Modifiers.end())
            {
                for (const auto &m : Modifiers.at(ItemModifierTrigger::Attack))
                {
                    name += " of " + m.Name;
                }
            }
        }
        else
        {
            if (Modifiers.find(ItemModifierTrigger::Defend) != Modifiers.end())
            {
                for (const auto &m : Modifiers.at(ItemModifierTrigger::Defend))
                {
                    name += " of " + m.Name;
                }
            }
        }

        return name;
    }

    std::string StatPrefixes(ActorStatType statType)
    {
        switch (statType)
        {
        case ActorStatType::MaxHealth:
            return "Healthy";
            break;
        case ActorStatType::MaxEnergy:
            return "Energetic";
            break;
        case ActorStatType::Vitality:
            return "Vigorous";
            break;
        case ActorStatType::Strength:
            return "Strong";
            break;
        case ActorStatType::Dexterity:
            return "Agile";
            break;
        case ActorStatType::Intellect:
            return "Wise";
            break;
        default:
            return "";
            break;
        }
    }

    // Item building

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

    ItemAsset SwordAsset = {AssetKey::SwordGreyTexture, {"Sword", "Short Sword", "Long Sword", "Heavy Sword"}};
    ItemAsset AxeAsset = {AssetKey::AxeTexture, {"Hatchet", "Axe", "Heavy Axe", "Broad Axe"}};

    auto AllStatModTypes = {ActorStatType::MaxHealth, ActorStatType::MaxEnergy, ActorStatType::Vitality, ActorStatType::Strength, ActorStatType::Dexterity, ActorStatType::Intellect};

    auto AllItemModifiers = {&ItemModifierExtraHit, &ItemModifierLifeLeech, &ItemModifierSacrifice};

    static ItemBuilder WeaponBuilder = {
        .assets = {SwordAsset, AxeAsset},
        .statModTypes = AllStatModTypes,
        .minStatMods = 1,
        .maxStatMods = 4,
        .itemModTypes = AllItemModifiers,
        .minItemMods = 0,
        .maxItemMods = 2,
    };

    static std::unordered_map<ItemType, ItemBuilder> ItemBuilders = {
        {ItemType::OneHand, WeaponBuilder},
    };

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

    std::unique_ptr<Item> RandomConsumable()
    {
        return SkillBook();

        // switch (RandomInt(3))
        // {
        // case 0:
        //     return HealingPotion();
        //     break;
        // case 1:
        //     return ManaPotion();
        //     break;
        // case 2:
        //     return RejuvPotion();
        //     break;
        // default:
        //     return nullptr;
        // }
    }

    std::unique_ptr<Item> RandomItem()
    {
        return BuildItem(ItemType::OneHand);

        // switch (RandomInt(4))
        // {
        // case 0:
        //     return Dagger();
        //     break;
        // case 1:
        //     return ShortSword();
        //     break;
        // case 2:
        //     return LongSword();
        //     break;
        // case 3:
        //     return RandomConsumable();
        //     break;
        // default:
        //     return nullptr;
        // }
    }

} // namespace cm