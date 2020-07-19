#include "cm_item.h"
#include "cm_random.h"

namespace cm
{
    std::unordered_map<ActorStatType, std::string> StatPrefixes = {
        {ActorStatType::MaxHealth, "Healthy"},
        {ActorStatType::MaxEnergy, "Energetic"},
        {ActorStatType::Vitality, "Vigorous"},
        {ActorStatType::Strength, "Strong"},
        {ActorStatType::Dexterity, "Agile"},
        {ActorStatType::Intellect, "Wise"},
    };

    std::string Item::DisplayName()
    {
        // TODO: cache this display name once its generated, it will never change
        auto name = Name;

        // if (Type == ItemType::Consumable)
        // {
        //     if (Modifiers.find(ItemModifierTrigger::Use) != Modifiers.end())
        //     {
        //         for (auto &m : Modifiers.at(ItemModifierTrigger::Use))
        //         {
        //             name = m.Name + " " + name;
        //         }
        //     }
        // }
        // else if (Type == ItemType::OneHand || Type == ItemType::OffHand)
        // {
        //     for (const auto &s : StatModifiers)
        //     {
        //         name = StatPrefixes.at(s.GetStatType()) + " " + name;
        //     }

        //     if (Modifiers.find(ItemModifierTrigger::Attack) != Modifiers.end())
        //     {
        //         for (const auto &m : Modifiers.at(ItemModifierTrigger::Attack))
        //         {
        //             name += " of " + m.Name;
        //         }
        //     }
        // }
        // else
        // {
        //     if (Modifiers.find(ItemModifierTrigger::Defend) != Modifiers.end())
        //     {
        //         for (const auto &m : Modifiers.at(ItemModifierTrigger::Defend))
        //         {
        //             name += " of " + m.Name;
        //         }
        //     }
        // }

        return name;
    }

} // namespace cm