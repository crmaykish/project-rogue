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
        bool Visible = false;

    public:
        Enemy(GameWorld &world);

        void Update() override;
        void Render(Renderer &renderer) override;
    };

} // namespace cm

#endif // CM_ENEMY_H
