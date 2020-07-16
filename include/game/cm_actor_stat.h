#ifndef CM_ACTOR_STAT_H
#define CM_ACTOR_STAT_H

#include <memory>
#include <vector>
#include <unordered_map>

namespace cm
{
    enum struct ActorStatType
    {
        Health,
        Energy,
        Vitality,
        Strength,
        Dexterity,
        Intellect
    };

    enum struct ActorStatModifierType
    {
        Add,
        Multiply
    };

    class ActorStatModifier
    {
    private:
        uint32_t Id = 0;
        ActorStatType StatType;
        float Value = 0.0;
        ActorStatModifierType ModifierType = ActorStatModifierType::Add;

    public:
        ActorStatModifier(ActorStatType statType, float value, ActorStatModifierType modifierType);

        uint32_t GetId() const;
        float GetValue() const;
        ActorStatType GetStatType() const;
        ActorStatModifierType GetModifierType() const;
    };

    struct ActorStat
    {
        float BaseValue;
        std::vector<ActorStatModifier> Modifiers;
    };

    class ActorStatSet
    {
    private:
        bool cacheValid = false; // TODO: this has to be at the stat level

        // TODO: if we're storing the stat type in the modifiers anyway, might be no reason to keep this as a map except a slight improvement to lookup times
        std::unordered_map<ActorStatType, ActorStat> Stats;
        ActorStat *GetStat(ActorStatType statType);

        void InvalidateCache() { cacheValid = false; }

    public:
        /**
         * @brief Return the total value of a stat with all modifiers factored in
         */
        int GetStatValue(ActorStatType statType);

        /**
         * @brief Set the base value for a stat type. If the stat does not yet exist, create it and then set the base value
         */
        void SetStatBaseValue(ActorStatType statType, float baseValue);

        /**
         * @brief Add a modifier to increase or decrease the total of an actor's stat
         * 
         * @param statType The type of stat this is modifying
         * @param modifier Stat modifier to add to this stat type
         */
        void AddStatModifier(ActorStatType statType, ActorStatModifier modifier);

        /**
         * @brief Remove the modifier of the given ID from the stats list
         */
        void RemoveStatModifier(int modifierId);

        // Derived stats

        int GetAttackRating();
        int GetDefenseRating();
    };

} // namespace cm

#endif /* CM_ACTOR_STAT_H */
