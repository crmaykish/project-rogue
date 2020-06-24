#ifndef CM_PLAYER_H
#define CM_PLAYER_H

#include "cm_actor.h"
#include "cm_world.h"
#include "cm_renderer.h"
#include "cm_input.h"

namespace cm
{
    class Player : public Actor
    {
    private:
        World &CurrentWorld;
        UserInput &Input;
        Renderer &MainRenderer;

    public:
        Player(float x, float y, World &world, UserInput &input, Renderer &renderer);
        void Update() override;
        void Render() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
