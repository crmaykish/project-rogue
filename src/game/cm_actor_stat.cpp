#include <algorithm>
#include <math.h>
#include "cm_actor_stat.h"
#include "cm_logger.h"

namespace cm
{
    /**
     * @brief Global modifier ID counter. Whenever a new modifier is created, use this value as the ID and increment
     * Note: 0 is not a valid id and is reserved for errors
     */
    static uint32_t ModifierID = 1;

    ActorStatModifier::ActorStatModifier(ActorStatType statType, float value, ActorStatModifierType modifierType)
        : StatType(statType), Value(value), ModifierType(modifierType)
    {
        Id = ModifierID;
        ModifierID++;
    }

    uint32_t ActorStatModifier::GetId() const
    {
        return Id;
    }

    float ActorStatModifier::GetValue() const
    {
        return Value;
    }

    ActorStatType ActorStatModifier::GetStatType() const
    {
        return StatType;
    }

    ActorStatModifierType ActorStatModifier::GetModifierType() const
    {
        return ModifierType;
    }

    int ActorStatSet::GetStatValue(ActorStatType statType)
    {
        auto stat = GetStat(statType);

        if (stat == nullptr)
        {
            return 0;
        }

        auto value = stat->BaseValue;

        // Add modifiers
        for (const auto &mod : stat->Modifiers)
        {
            if (mod.GetModifierType() == ActorStatModifierType::Add)
            {
                value += mod.GetValue();
            }
        }

        for (const auto &mod : stat->Modifiers)
        {
            if (mod.GetModifierType() == ActorStatModifierType::Multiply)
            {
                value *= (1.0 + mod.GetValue());
            }
        }

        // Return the final stat value as a rounded int
        return static_cast<int>(std::round(value));
    }

    void ActorStatSet::SetStatBaseValue(ActorStatType statType, float baseValue)
    {
        auto stat = GetStat(statType);

        if (stat == nullptr)
        {
            // Create new stat
            Stats.emplace(statType, ActorStat{baseValue});
        }
        else
        {
            // Set the value
            stat->BaseValue = baseValue;
        }
    }

    void ActorStatSet::AddStatModifier(ActorStatType statType, ActorStatModifier modifier)
    {
        auto stat = GetStat(statType);

        if (stat != nullptr)
        {
            stat->Modifiers.emplace_back(modifier);
        }
        else
        {
            Log("Tried to add a modifier to a non-existent stat", LOG_WARNING);
        }
    }

    void ActorStatSet::RemoveStatModifier(int modifierId)
    {
        for (auto &stat : Stats)
        {
            stat.second.Modifiers.erase(std::remove_if(stat.second.Modifiers.begin(),
                                                       stat.second.Modifiers.end(),
                                                       [=](auto &a) { return a.GetId() == modifierId; }),
                                        stat.second.Modifiers.end());
        }
    }

    int ActorStatSet::GetAttackRating()
    {
        return GetStatValue(ActorStatType::Strength) * 1.5;
    }

    int ActorStatSet::GetDefenseRating()
    {
        return GetStatValue(ActorStatType::Dexterity) * 1.4;
    }

    int ActorStatSet::HP()
    {
        return GetStatValue(ActorStatType::Health);
    }

    int ActorStatSet::MaxHP()
    {
        return GetStatValue(ActorStatType::MaxHealth);
    }

    int ActorStatSet::Energy()
    {
        return GetStatValue(ActorStatType::Energy);
    }

    int ActorStatSet::MaxEnergy()
    {
        return GetStatValue(ActorStatType::MaxEnergy);
    }

    void ActorStatSet::AdjustEnergy(int energy)
    {
        SetStatBaseValue(ActorStatType::Energy, GetStatValue(ActorStatType::Energy) + energy);

        if (GetStatValue(ActorStatType::Energy) < 0)
        {
            SetStatBaseValue(ActorStatType::Energy, 0);
        }
        else if (GetStatValue(ActorStatType::Energy) > GetStatValue(ActorStatType::MaxEnergy))
        {
            SetStatBaseValue(ActorStatType::Energy, GetStatValue(ActorStatType::MaxEnergy));
        }
    }

    void ActorStatSet::AdjustHP(int hp)
    {
        SetStatBaseValue(ActorStatType::Health, GetStatValue(ActorStatType::Health) + hp);

        if (GetStatValue(ActorStatType::Health) < 0)
        {
            SetStatBaseValue(ActorStatType::Health, 0);
        }
        else if (GetStatValue(ActorStatType::Health) > GetStatValue(ActorStatType::MaxHealth))
        {
            SetStatBaseValue(ActorStatType::Health, GetStatValue(ActorStatType::MaxHealth));
        }
    }

    ActorStat *ActorStatSet::GetStat(ActorStatType statType)
    {
        if (Stats.find(statType) == Stats.end())
        {
            return nullptr;
        }

        return &Stats.at(statType);
    }

} // namespace cm