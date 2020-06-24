#include "cm_player.h"

namespace cm
{
    Player::Player(float x, float y, World &world, UserInput &input, Renderer &renderer)
        : Actor(x, y),
          CurrentWorld(world),
          Input(input),
          MainRenderer(renderer) {}

    void Player::Update()
    {
        if (Input.Right.Once())
        {
            // TODO move right
        }
        else if (Input.Left.Once())
        {
            // TODO move left
        }
    }

    void Player::Render()
    {
        MainRenderer.DrawRectangle(X, Y, TILE_SIZE, TILE_SIZE, COLOR_GREEN);
    }

} // namespace cm