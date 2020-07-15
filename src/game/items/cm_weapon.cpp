#include "cm_item.h"
#include "cm_random.h"
#include "cm_effect.h"

namespace cm
{
    static const int ModifierChance = 20;

    std::unique_ptr<Item> Dagger()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Dagger";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::DaggerTexture;
        item->BaseAttack = 1;

        // Stat modifiers
        item->AddStatModifier(ActorStatModifier(ActorStatType::Strength, 2, ActorStatModifierType::Add));

        // Behavior modifiers
        if (RandomPercentCheck(ModifierChance))
        {
            item->AddModifier(ItemModifierTrigger::Attack, RandomAttackModifier());
        }

        return item;
    }

    std::unique_ptr<Item> ShortSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Short Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordGreyTexture;
        item->BaseAttack = 3;

        return item;
    }

    std::unique_ptr<Item> LongSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Long Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordBlueTexture;
        item->BaseAttack = 5;

        return item;
    }

} // namespace cm