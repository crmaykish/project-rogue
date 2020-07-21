#ifndef CM_COMBAT_H
#define CM_COMBAT_H

namespace cm
{
    class Actor;
    class GameWorld;

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
        void Damage(ActorDamage damage, GameWorld &world);
        void Heal(ActorDamage healing, GameWorld &world);
    };

} // namespace cm

#endif /* CM_COMBAT_H */
