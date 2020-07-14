#include "cm_item.h"
#include "cm_random.h"

namespace cm
{
    void Item::Pickup(Actor &owner, GameWorld &world)
    {
        if (PickedUp)
        {
            return;
        }

        for (auto const &e : PickupEffects)
        {
            e->Use(owner, world);
        }

        PickedUp = true;
    }

    void Item::Use(Actor &owner, GameWorld &world)
    {
        if (Charges == 0)
        {
            return;
        }

        for (auto const &e : UseEffects)
        {
            e->Use(owner, world);
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

    std::string Item::DisplayName()
    {
        auto name = Name;

        if (UseEffects.size() > 0)
        {
            name += " of";

            for (auto &e : UseEffects)
            {
                name += " " + e->GetName();
            }
        }

        return name;
    }

    std::unique_ptr<Item> HealthPotion(int healing, int stackSize)
    {
        auto a = std::make_unique<Item>();
        a->Name = "Potion";
        a->TextureKey = AssetKey::HealthPotionTexture;
        a->Charges = stackSize;
        a->AddUseEffect(std::make_unique<HealEffect>(healing));

        return a;
    }

    std::unique_ptr<Item> Torch()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Torch";
        a->TextureKey = AssetKey::TorchTexture;
        a->AddPickupEffect(std::make_unique<AddTorchFuelEffect>());

        return a;
    }

    std::unique_ptr<Item> RustyDagger()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Rusty Dagger";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::DaggerTexture;
        a->BaseDamage = 1 + RandomInt(5); // 1 to 5 base damage

        return a;
    }

    std::unique_ptr<Item> Sword()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Longsword";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::SwordGreyTexture;
        a->BaseDamage = 5 + RandomInt(7); // 5 to 12 base damage

        return a;
    }

    std::unique_ptr<Item> LeatherHelmet()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Leather Helmet";
        a->Type = ItemType::Head;
        a->TextureKey = AssetKey::HelmetLeatherTexture;
        a->BaseArmor = 3 + RandomInt(3); // 3 to 6 base armor

        return a;
    }

    std::unique_ptr<Item> LeatherBoots()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Leather Boots";
        a->Type = ItemType::Boots;
        a->TextureKey = AssetKey::BootsLeatherTexture;
        a->BaseArmor = 1 + RandomInt(3); // 1 to 3 base armor

        return a;
    }

    std::unique_ptr<Item> Buckler()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Buckler";
        a->Type = ItemType::OffHand;
        a->TextureKey = AssetKey::BucklerTexture;
        a->BaseArmor = 8 + RandomInt(5); // 8 to 13 base armor

        return a;
    }

    std::unique_ptr<Item> Shield()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Shield";
        a->Type = ItemType::OffHand;
        a->TextureKey = AssetKey::ShieldTexture;
        a->BaseArmor = 15 + RandomInt(10); // 15 to 25 base armor

        return a;
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

    std::unique_ptr<Item> BattleAxe()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Battle Axe";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::BattleAxeTexture;
        a->BaseDamage = 15 + RandomInt(20); // 15-35 base damage
        a->BaseArmor = -1 - (RandomInt(3)); // -1 - -3 base armor
        return a;
    }

    std::unique_ptr<Item> Beer()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Beer";
        a->Type = ItemType::Consumable;
        a->TextureKey = AssetKey::BeerTexture;
        a->Charges = 1;
        return a;
    }

    std::unique_ptr<Item> Wine()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Wine";
        a->Type = ItemType::Consumable;
        a->TextureKey = AssetKey::WineTexture;
        a->Charges = 1;
        return a;
    }

    std::unique_ptr<Item> Club()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Club";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::ClubTexture;
        a->BaseDamage = 4;
        return a;
    }

    std::unique_ptr<Item> Falchion()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Falchion";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::FalchionTexture;
        a->BaseDamage = 10;
        return a;
    }

    std::unique_ptr<Item> Hammer()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Hammer";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::HammerTexture;
        a->BaseDamage = 12;
        return a;
    }

    std::unique_ptr<Item> TowerShield()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Tower Shield";
        a->Type = ItemType::OffHand;
        a->TextureKey = AssetKey::ShieldTowerTexture;
        a->BaseArmor = 20 + RandomInt(20);

        return a;
    }

    std::unique_ptr<Item> Staff()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Staff";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::StaffTexture;
        a->BaseDamage = 2;
        return a;
    }

    std::unique_ptr<Item> Wand()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Wand";
        a->Type = ItemType::OneHand;
        a->TextureKey = AssetKey::WandBlueTexture;
        a->BaseDamage = 4;
        a->Charges = 999; // TODO: make charges optional

        a->AddUseEffect(std::make_unique<HealEffect>(5));
        a->AddUseEffect(std::make_unique<RandomPotionSpawnEffect>());

        return a;
    }

    std::unique_ptr<Item> Charm()
    {
        auto a = std::make_unique<Item>();
        a->Name = "Charm";
        a->Type = ItemType::Charm;
        a->TextureKey = AssetKey::CharmBlueTexture;
        return a;
    }

    std::unique_ptr<Item> RandomConsumable()
    {
        switch (RandomInt(4))
        {
        case 0:
            return HealthPotion(15);
            break;
        case 1:
            return Torch();
            break;
        case 2:
            return Wine();
            break;
        case 3:
            return Beer();
            break;
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Item> RandomWeapon()
    {
        switch (RandomInt(12))
        {
        case 0:
            return RustyDagger();
            break;
        case 1:
            return Sword();
            break;
        case 2:
            return Bow();
            break;
        case 3:
            return Crossbow();
            break;
        case 4:
            return SpellBook();
            break;
        case 5:
            return Axe();
            break;
        case 6:
            return BattleAxe();
            break;
        case 7:
            return Club();
            break;
        case 8:
            return Falchion();
            break;
        case 9:
            return Hammer();
            break;
        case 10:
            return Staff();
            break;
        case 11:
            return Wand();
            break;
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Item> RandomArmor()
    {
        switch (RandomInt(6))
        {
        case 0:
            return LeatherBoots();
            break;
        case 1:
            return LeatherHelmet();
            break;
        case 2:
            return Buckler();
            break;
        case 3:
            return Shield();
            break;
        case 4:
            return TowerShield();
            break;
        case 5:
            return Charm();
            break;
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Item> RandomItem()
    {
        switch (RandomInt(3))
        {
        case 0:
            return RandomConsumable();
            break;
        case 1:
            return RandomWeapon();
            break;
        case 2:
            return RandomArmor();
            break;
        default:
            return nullptr;
        }
    }

} // namespace cm