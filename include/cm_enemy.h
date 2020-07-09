#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Enemy : public Actor
    {
    public:
        Enemy(int x, int y);
        void Update(GameWorld &world) override;
        void Render(const Renderer &renderer) override;
        void Reset() override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(GameWorld &world) override;

        int GetAttack() override;
        int GetDefense() override;

        Inventory *GetInventory() override;
    };

} // namespace cm

#endif // CM_ENEMY_H
