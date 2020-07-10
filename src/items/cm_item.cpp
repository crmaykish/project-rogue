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

    std::unique_ptr<Item> Buckler()
    {
        auto buckler = std::make_unique<Item>();
        buckler->Name = "Buckler";
        buckler->Type = ItemType::OffHand;
        buckler->TextureKey = AssetKey::BucklerTexture;
        buckler->BaseArmor = 8 + RandomInt(5); // 8 to 13 base armor

        return buckler;
    }

    std::unique_ptr<Item> Shield()
    {
        auto shield = std::make_unique<Item>();
        shield->Name = "Shield";
        shield->Type = ItemType::OffHand;
        shield->TextureKey = AssetKey::ShieldTexture;
        shield->BaseArmor = 15 + RandomInt(10); // 15 to 25 base armor

        return shield;
    }

    std::unique_ptr<Item> Bow()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Bow";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::BowTexture;
        a->BaseDamage = 10 + RandomInt(5); // 10 to 15 base damage
        return a;
    }

    std::unique_ptr<Item> Crossbow()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Crossbow";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::CrossbowTexture;
        a->BaseDamage = 8 + RandomInt(12); // 8-20 base damage
        return a;
    }

    std::unique_ptr<Item> SpellBook()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Spellbook";
        a->Type = ItemType::OffHand;
        a->TextureKey = AssetKey::BookBlueTexture;
        return a;
    }

    std::unique_ptr<Item> Axe()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Axe";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::AxeTexture;
        a->BaseDamage = 12 + RandomInt(12); // 12-24 base damage
        return a;
    }

    std::unique_ptr<Item> RandomItem()
    {
        switch (RandomInt(12))
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
        case 6:
            return Buckler();
            break;
        case 7:
            return Shield();
            break;
        case 8:
            return Bow();
            break;
        case 9:
            return Crossbow();
            break;
        case 10:
            return SpellBook();
            break;
        case 11:
            return Axe();
            break;
        default:
            return nullptr;
        }
    }

} // namespace cm