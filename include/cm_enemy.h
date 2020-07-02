#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Enemy : public Actor
    {
    public:
        Enemy(int x, int y);
        void Update(const GameWorld &world) override;
        void Render(const Renderer &renderer) override;
        void Reset() override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(const GameWorld &world) override;

        int GetAttack() override;

        Inventory *GetInventory() override;

        int GetViewDistance() override;
    };

} // namespace cm

#endif // CM_ENEMY_H
