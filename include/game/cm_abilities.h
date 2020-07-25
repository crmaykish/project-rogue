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

    // TODO: define ability result enum instead of bool

    // TODO: abilities should have cooldowns (turns between uses)

    class Ability
    {
    public:
        virtual ~Ability() {}
        virtual std::string GetName() = 0;
        virtual std::string GetDescription() = 0;
        virtual AssetKey GetIcon() = 0;
        virtual bool IsSelfCast() { return false; }
        virtual int EnergyCost() { return 1; }

        // Presumably an ability will always effect the user or the game world or both
        virtual bool Use(Actor &user, GameWorld &world) = 0;
    };

    class AbilitySet
    {
    private:
        std::array<std::unique_ptr<Ability>, AbilitiesSetSize> Abilities;

    public:
        void SetAbility(int slot, std::unique_ptr<Ability> ability);
        Ability *AbilityAt(int slot);
        bool AbilityReady(int slot);
        int FreeSlot();
        void Reset();
    };

    class AttackAbility : public Ability
    {
    public:
        std::string GetName() override { return "Attack"; }
        std::string GetDescription() override { return "Attack with your weapon"; }
        AssetKey GetIcon() override { return AssetKey::MeleeIcon; }
        int EnergyCost() override { return 1; }
        bool Use(Actor &user, GameWorld &world) override;
    };

    class CleaveAbility : public Ability
    {
    public:
        std::string GetName() override { return "Cleave"; }
        std::string GetDescription() override { return "Attack all enemies within 1 tile"; };
        AssetKey GetIcon() override { return AssetKey::CleaveIcon; };
        bool IsSelfCast() override { return true; }
        int EnergyCost() override { return 3; }
        bool Use(Actor &user, GameWorld &world) override;
    };

    class HealAbility : public Ability
    {
    public:
        std::string GetName() override { return "Heal"; }
        std::string GetDescription() override { return "Heal yourself for 40\% of max HP"; }
        AssetKey GetIcon() override { return AssetKey::HealIcon; };
        bool IsSelfCast() override { return true; }
        int EnergyCost() override { return 3; }
        bool Use(Actor &user, GameWorld &world) override;
    };

    class TeleportAbility : public Ability
    {
    public:
        std::string GetName() override { return "Teleport"; }
        std::string GetDescription() override { return "Instantly move up to 4 tiles away"; }
        AssetKey GetIcon() override { return AssetKey::TeleportIcon; };
        int EnergyCost() override { return 3; }
        bool Use(Actor &user, GameWorld &world) override;
    };

    class SlimeSplitAbility : public Ability
    {
        std::string GetName() override { return "Split"; }
        std::string GetDescription() override { return "Splits into two smaller slimes"; }
        AssetKey GetIcon() override { return AssetKey::Unknown; };
        bool IsSelfCast() override { return true; }
        int EnergyCost() override { return 2; }
        bool Use(Actor &user, GameWorld &world) override;
    };

    std::unique_ptr<Ability> RandomAbility();

} // namespace cm

#endif /* CM_ABILITIES_H */
