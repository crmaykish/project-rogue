#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Enemy : public Actor
    {
    protected:
    public:
        AssetKey Texture = AssetKey::Unknown;
        Enemy(Point position);
        virtual ~Enemy(){};
        virtual void Tick(GameWorld &world) override;
        void Update(GameWorld &world) override;
        virtual void Render(const Renderer &renderer) override;
        bool ActionReady() override;
    };

    class Slime : public Enemy
    {
    private:
        bool SpottedPlayer = false;
        int TurnsToSplit = 5;

    public:
        Slime(Point position);
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
        void Tick(GameWorld &world) override;
    };

    class Ghost : public Enemy
    {
    public:
        Ghost(Point position);
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
    };

    class Spider : public Enemy
    {
    public:
        Spider(Point position);
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
    };

    class Balrog : public Enemy
    {
    private:
        bool Awake = false;

    public:
        Balrog(Point position);
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
        void Render(const Renderer &renderer) override;
    };

    std::unique_ptr<Actor> RandomEnemy(Point position);

} // namespace cm

#endif // CM_ENEMY_H
