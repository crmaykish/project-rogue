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
        // TODO: cache this display name once it's generated, it will never change
        auto name = Name;

        if (Type == ItemType::Consumable)
        {
        }
        else
        {
            for (const auto &s : StatModifiers)
            {
                name = StatPrefixes.at(s.GetStatType()) + " " + name;
            }
        }

        // TODO: need a better way to loop through an EffectMap
        for (const auto &a : Effects.Effects)
        {
            for (const auto &b : a.second)
            {
                name += " of " + b->GetName();
            }
        }

        return name;
    }

} // namespace cm