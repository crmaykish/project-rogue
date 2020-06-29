#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_renderer.h"

namespace cm
{
    class Enemy : public Actor
    {
    private:
        GameWorld &World;

    public:
        Enemy(GameWorld &world, int x, int y);
        std::string GetName() override;
        int GetAttack() override;
        void Update() override;
        std::shared_ptr<Action> NextAction() override;
        void Render(Renderer &renderer) override;
        Faction GetFaction() override;

        void Reset() override;
    };

} // namespace cm

#endif // CM_ENEMY_H
