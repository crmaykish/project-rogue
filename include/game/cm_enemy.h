#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Behavior
    {
    public:
        virtual void Use(Actor &actor, GameWorld &world) = 0;
    };

    class SlimeBehavior : public Behavior
    {
    private:
        int DamagedTurns = 0;

    public:
        void Use(Actor &actor, GameWorld &world) override;
    };

    class Enemy : public Actor
    {
    public:
        AssetKey Texture = AssetKey::Unknown;
        std::unique_ptr<Behavior> BehaviorComp;

        Enemy(int x, int y);
        void Update(GameWorld &world) override;
        void Tick(GameWorld &world) override;
        void Render(const Renderer &renderer) override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
    };

    std::unique_ptr<Actor> Slime(int x, int y, int level);
    std::unique_ptr<Actor> RandomEnemy(int x, int y, int level);

} // namespace cm

#endif // CM_ENEMY_H
