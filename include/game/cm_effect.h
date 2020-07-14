#ifndef CM_EFFECT_H
#define CM_EFFECT_H

namespace cm
{
    class Actor;
    class GameWorld;

    class Effect
    {
    public:
        virtual ~Effect() {}
        virtual void Use(Actor *source, Actor *dest, GameWorld *world) = 0;
    };

    class HealEffect : public Effect
    {
    private:
        int Health = 10;

    public:
        HealEffect(int health);
        void Use(Actor *source, Actor *dest, GameWorld *world) override;
    };

    class AddTorchFuelEffect : public Effect
    {
    public:
        void Use(Actor *source, Actor *dest, GameWorld *world) override;
    };

    class DamageEffect : public Effect
    {
    private:
        int Damage = 10;

    public:
        DamageEffect(int damage);
        void Use(Actor *source, Actor *dest, GameWorld *world) override;
    };

} // namespace cm

#endif // CM_EFFECT_H
