#ifndef CM_ABILITIES_H
#define CM_ABILITIES_H

#include <memory>
#include <array>
#include <string>

#include "cm_assets.h"

namespace cm
{
    class Actor;
    class GameWorld;

    const int AbilitiesSetSize = 4;

    class Ability
    {
    public:
        virtual ~Ability() {}
        virtual std::string GetName() = 0;
        virtual std::string GetDescription() = 0;
        
        virtual AssetKey GetIcon() = 0;

        // Presumably an ability will always effect the user or the game world or both
        virtual bool Use(Actor &user, GameWorld &world) = 0;
    };

    class AbilitySet
    {
    private:
        std::array<std::unique_ptr<Ability>, AbilitiesSetSize> Abilities;

    public:
        void SetAbility(int slot, std::unique_ptr<Ability> ability);
        bool UseAbility(int slot, Actor &user, GameWorld &world);
        Ability *AbilityAt(int slot);
        bool AbilityReady(int slot);
    };

    // TODO: Basic melee and ranged attacks should also be Abilities?

    class HealAbility : public Ability
    {
    public:
        std::string GetName() override;
        std::string GetDescription() override;
        AssetKey GetIcon() override;
        bool Use(Actor &user, GameWorld &world) override;
    };

    class CleaveAbility : public Ability
    {
        std::string GetName() override;
        std::string GetDescription() override;
        AssetKey GetIcon() override;
        bool Use(Actor &user, GameWorld &world) override;
    };

} // namespace cm

#endif /* CM_ABILITIES_H */
