#include "cm_item.h"

namespace cm
{
    std::unique_ptr<Item> HealingPotion()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Potion";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::HealthPotionTexture;
        item->AddOnUseModifier("of Healing", std::make_unique<HealEffect>(40));

        return item;
    }

    std::unique_ptr<Item> ManaPotion()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Potion";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::EnergyPotionTexture;
        item->AddOnUseModifier("of Mana", std::make_unique<ManaEffect>(20));

        return item;
    }

} // namespace cm