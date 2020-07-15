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

        if (RandomInt(100) < ModifierChance)
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

        if (RandomInt(100) < ModifierChance)
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
        item->BaseAttack = 5;

        if (RandomInt(100) < ModifierChance)
        {
            for (int i = 0; i <= RandomInt(3); i++)
            {
                item->AddModifier(ItemModifierTrigger::Attack, RandomAttackModifier());
            }
        }

        return item;
    }

} // namespace cm