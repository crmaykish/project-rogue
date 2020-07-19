#ifndef CM_COMBAT_H
#define CM_COMBAT_H

namespace cm
{
    class Actor;

    struct ActorDamage
    {
        int Value = 0;
        Actor *Source = nullptr;
    };

    class Combat
    {
    private:
        Actor &Owner;

    public:
        Combat(Actor &owner);
        void Damage(ActorDamage damage);
    };

} // namespace cm

#endif /* CM_COMBAT_H */
