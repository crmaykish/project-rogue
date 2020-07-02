#ifndef CM_EFFECT_H
#define CM_EFFECT_H

namespace cm
{
    class Actor;
    class Item;

    class Effect
    {
    public:
        virtual ~Effect() {}
        virtual void Use(Actor &target) = 0;
    };

    class HealEffect : public Effect
    {
    private:
        int Health = 10;

    public:
        HealEffect(int health);
        void Use(Actor &target) override;
    };

    class AddTorchFuelEffect : public Effect
    {
    public:
        void Use(Actor &target) override;
    };

} // namespace cm

#endif // CM_EFFECT_H
