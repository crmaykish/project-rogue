#include "cm_player.h"
#include "cm_tile.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input, Renderer &renderer)
        : World(world),
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
        MainRenderer.DrawRectangle(X, Y, TileSize, TileSize, COLOR_GREEN);
    }

} // namespace cm