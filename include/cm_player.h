#ifndef CM_PLAYER_H
#define CM_PLAYER_H

#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_input.h"
#include "cm_renderer.h"

namespace cm
{
    class Player : public Actor
    {
    private:
        GameWorld &World;
        UserInput &Input;
        Renderer &MainRenderer;

    public:
        Player(GameWorld &world, UserInput &input, Renderer &renderer);
        void Update() override;
        void Render() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
