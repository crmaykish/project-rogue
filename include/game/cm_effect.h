#ifndef CM_EFFECT_H
#define CM_EFFECT_H

#include <string>

namespace cm
{
    class Actor;
    class GameWorld;

    // TODO: effects should have some way of accessing their status for event logging

    class Effect
    {
    public:
        virtual ~Effect() {}
        virtual void Use(Actor &target, GameWorld &world) = 0;
        virtual std::string GetName() = 0;
    };

    class NullEffect : public Effect
    {
    public:
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

    class HealEffect : public Effect
    {
    private:
        int Health = 10;

    public:
        HealEffect(int health);
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

    class AddTorchFuelEffect : public Effect
    {
    public:
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

    class DamageEffect : public Effect
    {
    private:
        int Damage = 10;

    public:
        DamageEffect(int damage);
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

    class RandomPotionSpawnEffect : public Effect
    {
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

    class LifeStealEffect : public Effect
    {
    public:
        void Use(Actor &target, GameWorld &world) override;
        std::string GetName() override;
    };

} // namespace cm

#endif // CM_EFFECT_H
