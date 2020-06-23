#ifndef CM_COMPONENT_PLAYER_MOVEMENT_H
#define CM_COMPONENT_PLAYER_MOVEMENT_H

#include "cm_component.h"
#include "cm_actor.h"
#include "cm_input.h"

namespace cm
{
    class PlayerMovementComponent : public Component
    {
    private:
        std::shared_ptr<Actor> Player;
        UserInput &Input;

    public:
        PlayerMovementComponent(std::shared_ptr<Actor> player, UserInput &userInput);
        void OnUpdate() override;
        void OnRender() override;
    };
} // namespace cm

#endif // CM_COMPONENT_PLAYER_MOVEMENT_H
