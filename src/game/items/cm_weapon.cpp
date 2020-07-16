#include "cm_item.h"
#include "cm_random.h"
#include "cm_effect.h"

namespace cm
{
    std::unique_ptr<Item> Dagger()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Dagger";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::DaggerTexture;

        // Stat modifiers
        item->AddStatModifier(ActorStatModifier(ActorStatType::Strength, 1, ActorStatModifierType::Add));

        return item;
    }

    std::unique_ptr<Item> ShortSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Short Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordGreyTexture;

        if (RandomPercentCheck(50))
        {
            item->AddStatModifier(ActorStatModifier(ActorStatType::Strength, 2, ActorStatModifierType::Add));
        }
        else
        {
            item->AddStatModifier(ActorStatModifier(ActorStatType::Dexterity, 2, ActorStatModifierType::Add));
        }

        // Behavior modifiers
        if (RandomPercentCheck(10))
        {
            item->AddModifier(ItemModifierTrigger::Attack, RandomAttackModifier());
        }

        return item;
    }

    std::unique_ptr<Item> LongSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Long Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordBlueTexture;

        if (RandomPercentCheck(50))
        {
            item->AddStatModifier(ActorStatModifier(ActorStatType::Strength, RandomInt(2, 5), ActorStatModifierType::Add));
        }
        else
        {
            item->AddStatModifier(ActorStatModifier(ActorStatType::Dexterity, RandomInt(2, 5), ActorStatModifierType::Add));
        }

        // Behavior modifiers
        if (RandomPercentCheck(20))
        {
            item->AddModifier(ItemModifierTrigger::Attack, RandomAttackModifier());
        }

        return item;
    }

} // namespace cm