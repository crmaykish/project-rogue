#include "cm_item.h"
#include "cm_random.h"

namespace cm
{
    void Item::Use(ItemModifierTrigger trigger, Actor &owner, GameWorld &world)
    {
        if (LimitedCharge && Charges == 0)
        {
            return;
        }

        if (Modifiers.find(trigger) != Modifiers.end())
        {
            for (auto const &mod : Modifiers.at(trigger))
            {
                if (RandomInt(100) < mod.PercentChance)
                {
                    mod.MainEffect->Use(owner, world);
                }
            }
        }

        Charges--;
    }

    void Item::AddModifier(ItemModifierTrigger trigger, ItemModifier modifier)
    {
        if (Modifiers.find(trigger) == Modifiers.end())
        {
            // Vector at this trigger is empty, create it before trying to insert a new modifier
            Modifiers.emplace(trigger, std::vector<ItemModifier>());
        }

        Modifiers.at(trigger).push_back(std::move(modifier));
    }

    AssetKey Item::GetTextureKey()
    {
        return TextureKey;
    }

    std::string Item::DisplayName()
    {
        // TODO: cache this display name once its generated, it will never change
        auto name = Name;

        if (Type == ItemType::Consumable)
        {
            if (Modifiers.find(ItemModifierTrigger::Use) != Modifiers.end())
            {
                for (auto &m : Modifiers.at(ItemModifierTrigger::Use))
                {
                    name = m.Name + " " + name;
                }
            }
        }
        else if (Type == ItemType::OneHand || Type == ItemType::OffHand)
        {
            if (Modifiers.find(ItemModifierTrigger::Attack) != Modifiers.end())
            {
                for (auto &m : Modifiers.at(ItemModifierTrigger::Attack))
                {
                    name += " of " + m.Name;
                }
            }
        }
        else
        {
            if (Modifiers.find(ItemModifierTrigger::Defend) != Modifiers.end())
            {
                for (auto &m : Modifiers.at(ItemModifierTrigger::Defend))
                {
                    name += " of " + m.Name;
                }
            }
        }

        return name;
    }

    std::unique_ptr<Item> RandomConsumable()
    {
        switch (RandomInt(3))
        {
        case 0:
            return HealingPotion();
            break;
        case 1:
            return ManaPotion();
            break;
        case 2:
            return RejuvPotion();
            break;
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Item> RandomItem()
    {
        switch (RandomInt(4))
        {
        case 0:
            return Dagger();
            break;
        case 1:
            return ShortSword();
            break;
        case 2:
            return LongSword();
            break;
        case 3:
            return RandomConsumable();
            break;
        default:
            return nullptr;
        }
    }

} // namespace cm