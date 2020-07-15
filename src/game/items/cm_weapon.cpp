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
        item->BaseDamage = 1;

        item->AddModifier(ItemModifierTrigger::Attack, ItemModifierSacrifice());

        return item;
    }

    std::unique_ptr<Item> ShortSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Short Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordGreyTexture;
        item->BaseDamage = 5;

        item->AddModifier(ItemModifierTrigger::Attack, ItemModifierLifeLeech());

        return item;
    }

    std::unique_ptr<Item> LongSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Long Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordBlueTexture;
        item->BaseDamage = 8;

        item->AddModifier(ItemModifierTrigger::Attack, ItemModifierExtraHit());

        return item;
    }

} // namespace cm