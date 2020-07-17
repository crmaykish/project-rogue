#include "cm_item.h"

namespace cm
{
    std::unique_ptr<Item> HealingPotion()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Potion";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::HealthPotionTexture;
        item->LimitedCharge = true;
        item->Charges = 1;

        item->AddModifier(ItemModifierTrigger::Use, ItemModifierHeal());

        return item;
    }

    std::unique_ptr<Item> ManaPotion()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Potion";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::EnergyPotionTexture;
        item->LimitedCharge = true;
        item->Charges = 1;

        item->AddModifier(ItemModifierTrigger::Use, ItemModifierMana());

        return item;
    }

    std::unique_ptr<Item> RejuvPotion()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Potion";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::RejuvPotionTexture;
        item->LimitedCharge = true;
        item->Charges = 1;

        item->AddModifier(ItemModifierTrigger::Use, ItemModifierRejuv());

        return item;
    }

    std::unique_ptr<Item> SkillBook()
    {
        auto item = std::make_unique<Item>();
        item->Name = "Book";
        item->Type = ItemType::Consumable;
        item->TextureKey = AssetKey::BookBlueTexture;
        item->LimitedCharge = true;
        item->Charges = 1;

        item->AddModifier(ItemModifierTrigger::Use, ItemModifierLearnAbility());

        return item;
    }

} // namespace cm