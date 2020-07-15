#ifndef CM_EFFECT_H
#define CM_EFFECT_H

#include <string>

namespace cm
{
    class Actor;
    class GameWorld;

    /**
     * @brief An Effect is the preferred way to update the state of an Actor
     * Effects can change actor properties, e.g. HP, mana. They can also impact
     * the target's target (e.g. life-steal) or the world (e.g. AoE damage).
     */
    class Effect
    {
    public:
        virtual ~Effect() {}
        virtual void Use(Actor &actor, GameWorld &world) = 0;
    };

    /**
     * @brief Heal the actor
     */
    class HealEffect : public Effect
    {
    private:
        int Health = 0;

    public:
        HealEffect(int health);
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Restore the actor's mana
     */
    class ManaEffect : public Effect
    {
    private:
        int Mana = 0;

    public:
        ManaEffect(int mana);
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Restore the actor's health and mana
     */
    class RejuvEffect : public Effect
    {
    private:
        int Health = 0;
        int Mana = 0;

    public:
        RejuvEffect(int health, int mana);
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Increase the actor's torch fuel level
     */
    class AddTorchFuelEffect : public Effect
    {
    public:
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Damage the actor
     */
    class DamageEffect : public Effect
    {
    private:
        int Damage = 0;

    public:
        DamageEffect(int damage);
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Damage the actor's target
     */
    class DamageTargetEffect : public Effect
    {
    private:
        int Damage = 0;

    public:
        DamageTargetEffect(int damage);
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Spawn a random consumable in the actor's inventory
     */
    class RandomConsumableEffect : public Effect
    {
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Steal life from the actor's target to the actor
     */
    class LifeStealEffect : public Effect
    {
    public:
        void Use(Actor &actor, GameWorld &world) override;
    };

    /**
     * @brief Grant experience to the target actor
     */
    class ExperienceEffect : public Effect
    {
    private:
        int Experience;

    public:
        ExperienceEffect(int exp);
        void Use(Actor &actor, GameWorld &world) override;
    };

} // namespace cm

#endif // CM_EFFECT_H
