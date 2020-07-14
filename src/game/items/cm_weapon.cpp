#include "cm_item.h"
#include "cm_random.h"

namespace cm
{
    std::unique_ptr<Item> Dagger()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Dagger";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::DaggerTexture;
        item->BaseDamage = 1;

        item->AddOnUseModifier("of the Leech",
                               std::make_unique<LifeStealEffect>(),
                               10 + RandomInt(20));

        item->AddOnUseModifier("of Ages",
                               std::make_unique<ExperienceEffect>(20),
                               5 + RandomInt(5));

        item->AddOnUseModifier("of Vision",
                               std::make_unique<AddTorchFuelEffect>(),
                               5 + RandomInt(5));

        item->AddOnUseModifier("of Persistence",
                               std::make_unique<DamageTargetEffect>(5),
                               30 + RandomInt(20));

        item->AddOnUseModifier("of Gluttony",
                               std::make_unique<RandomConsumableEffect>(),
                               2 + RandomInt(3));

        return item;
    }

    std::unique_ptr<Item> ShortSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Short Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordGreyTexture;
        item->BaseDamage = 5;

        return item;
    }

    std::unique_ptr<Item> LongSword()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Long Sword";
        item->Type = ItemType::OneHand;
        item->TextureKey = AssetKey::SwordBlueTexture;
        item->BaseDamage = 8;

        return item;
    }

} // namespace cm