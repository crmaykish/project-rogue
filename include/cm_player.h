#ifndef CM_PLAYER_H
#define CM_PLAYER_H

#include <memory>
#include "cm_actor.h"
#include "cm_world.h"
#include "cm_renderer.h"
#include "cm_input.h"

namespace cm
{
    class Player : public Actor
    {
    private:
        std::shared_ptr<World> CurrentWorld;
        UserInput &Input;
        std::shared_ptr<Renderer> MainRenderer;

    public:
        Player(float x, float y, std::shared_ptr<World> world, UserInput &input, std::shared_ptr<Renderer> renderer);
        void Update() override;
        void Render() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
