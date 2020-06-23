#include "cm_component_player_movement.h"
#include "cm_world.h"

namespace cm
{
    PlayerMovementComponent::PlayerMovementComponent(std::shared_ptr<Actor> player, UserInput &userInput)
        : Player(player),
          Input(userInput) {}

    void PlayerMovementComponent::OnUpdate()
    {
        if (Input.Left.Once())
        {
            Player->Move(-TILE_SIZE, 0);
        }
        else if (Input.Right.Once())
        {
            Player->Move(TILE_SIZE, 0);
        }
        else if (Input.Up.Once())
        {
            Player->Move(0, TILE_SIZE);
        }
        else if (Input.Down.Once())
        {
            Player->Move(0, -TILE_SIZE);
        }
    }

    void PlayerMovementComponent::OnRender()
    {
    }
}