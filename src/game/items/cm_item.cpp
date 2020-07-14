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
        if (LimitedCharge && Charges == 0)
        {
            return;
        }

        for (auto const &e : OnUseModifiers)
        {
            if (RandomInt(100) < e.PercentChance)
            {
                e.MainEffect->Use(owner, world);
            }
        }

        Charges--;
    }

    void Item::AddPickupEffect(std::unique_ptr<Effect> effect)
    {
        PickupEffects.emplace_back(std::move(effect));
    }

    void Item::AddOnUseModifier(std::string name, std::unique_ptr<Effect> effect, int percentChance)
    {
        OnUseModifiers.emplace_back(ItemModifier{name, percentChance, std::move(effect)});
    }

    AssetKey Item::GetTextureKey()
    {
        return TextureKey;
    }

    std::string Item::DisplayName()
    {
        auto name = Name;

        if (OnUseModifiers.size() > 0)
        {
            for (auto &e : OnUseModifiers)
            {
                name += " " + e.Name;
            }
        }

        return name;
    }

    std::unique_ptr<Item> RandomConsumable()
    {
        return HealingPotion();
    }

    std::unique_ptr<Item> RandomItem()
    {
        return Dagger();

        // switch (RandomInt(3))
        // {
        // case 0:
        //     return Dagger();
        //     break;
        // case 1:
        //     return ShortSword();
        //     break;
        // case 2:
        //     return LongSword();
        //     break;
        // default:
        //     return nullptr;
        // }
    }

} // namespace cm