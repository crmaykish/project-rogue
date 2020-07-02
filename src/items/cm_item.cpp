#include "cm_item.h"

namespace cm
{
    void Item::Pickup(Actor &owner)
    {
        if (PickedUp)
        {
            return;
        }

        for (auto const &e : PickupEffects)
        {
            e->Use(owner);
        }

        PickedUp = true;
    }

    void Item::Use(Actor &owner)
    {
        if (Charges == 0)
        {
            return;
        }

        for (auto const &e : UseEffects)
        {
            e->Use(owner);
        }

        Charges--;
    }

    void Item::AddPickupEffect(std::unique_ptr<Effect> effect)
    {
        PickupEffects.emplace_back(std::move(effect));
    }

    void Item::AddUseEffect(std::unique_ptr<Effect> effect)
    {
        UseEffects.emplace_back(std::move(effect));
    }

    AssetKey Item::GetTextureKey()
    {
        return TextureKey;
    }

    std::unique_ptr<Item> HealthPotion(int healing, int stackSize)
    {
        auto hp = std::make_unique<Item>();
        hp->Name = "Health Potion";
        hp->TextureKey = AssetKey::HealthPotionTexture;
        hp->Charges = stackSize;
        hp->AddUseEffect(std::make_unique<HealEffect>(healing));

        return hp;
    }

    std::unique_ptr<Item> Torch()
    {
        auto torch = std::make_unique<Item>();
        torch->Name = "Torch";
        torch->TextureKey = AssetKey::TorchTexture;
        torch->Charges = 0;
        torch->AddPickupEffect(std::make_unique<AddTorchFuelEffect>());

        return torch;
    }

} // namespace cm