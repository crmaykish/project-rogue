#include "cm_player.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input) : World(world), Input(input) {}

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

    void Player::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(X, Y, TileSize, TileSize, COLOR_GREEN);
    }

} // namespace cm