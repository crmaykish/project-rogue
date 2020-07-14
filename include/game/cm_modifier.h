#ifndef CM_MODIFIER_H
#define CM_MODIFIER_H

namespace cm
{
    class GameWorld;
    class Actor;

    class Modifier
    {
    public:
        virtual void Modify(GameWorld &world) = 0;
    };

    // Chance to spawn a random potion
    class RandomPotionSpawnModifier : public Modifier
    {
    public:
        void Modify(GameWorld &world) override;
    };

} // namespace cm

#endif /* CM_MODIFIER_H */
