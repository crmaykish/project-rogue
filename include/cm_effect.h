#ifndef CM_EFFECT_H
#define CM_EFFECT_H

namespace cm
{
    class Actor;    // TODO: this seems wrong, better way to structure this?

    class Effect
    {
    public:
        virtual ~Effect();
        virtual void Use(Actor &target) = 0;
    };

    class HealEffect : public Effect
    {
    private:
        int Health = 10;
    public:
        // HealEffect(int health);
        void Use(Actor &target) override;
    };
}

#endif // CM_EFFECT_H
