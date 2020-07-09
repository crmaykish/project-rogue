#include "cm_item.h"
#include "cm_random.h"

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
        torch->AddPickupEffect(std::make_unique<AddTorchFuelEffect>());

        return torch;
    }

    std::unique_ptr<Item> RustyDagger()
    {
        auto dagger = std::make_unique<Item>();
        dagger->Name = "Rusty Dagger";
        dagger->Type = ItemType::OneHand;
        dagger->TextureKey = AssetKey::DaggerTexture;
        dagger->BaseDamage = 1 + RandomInt(5); // 1 to 5 base damage

        return dagger;
    }

    std::unique_ptr<Item> Sword()
    {
        auto sword = std::make_unique<Item>();
        sword->Name = "Longsword";
        sword->Type = ItemType::OneHand;
        sword->TextureKey = AssetKey::SwordGreyTexture;
        sword->BaseDamage = 5 + RandomInt(7); // 5 to 12 base damage

        return sword;
    }

    std::unique_ptr<Item> LeatherHelmet()
    {
        auto helmet = std::make_unique<Item>();
        helmet->Name = "Leather Helmet";
        helmet->Type = ItemType::Head;
        helmet->TextureKey = AssetKey::HelmetLeatherTexture;
        helmet->BaseArmor = 3 + RandomInt(3); // 3 to 6 base armor

        return helmet;
    }

    std::unique_ptr<Item> LeatherBoots()
    {
        auto boots = std::make_unique<Item>();
        boots->Name = "Leather Boots";
        boots->Type = ItemType::Boots;
        boots->TextureKey = AssetKey::BootsLeatherTexture;
        boots->BaseArmor = 1 + RandomInt(3); // 1 to 3 base armor

        return boots;
    }

    std::unique_ptr<Item> RandomItem()
    {
        switch (RandomInt(6))
        {
        case 0:
            return HealthPotion(15);
            break;
        case 1:
            return Torch();
            break;
        case 2:
            return RustyDagger();
            break;
        case 3:
            return Sword();
            break;
        case 4:
            return LeatherBoots();
            break;
        case 5:
            return LeatherHelmet();
            break;
        default:
            return nullptr;
        }
    }

} // namespace cm