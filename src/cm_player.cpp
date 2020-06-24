#include "cm_player.h"

namespace cm
{
    Player::Player(float x, float y,
                   std::shared_ptr<World> world,
                   UserInput &input,
                   std::shared_ptr<Renderer> renderer)
        : Actor(x, y),
          CurrentWorld(world),
          Input(input),
          MainRenderer(renderer) {}

    void Player::Update()
    {
        if (Input.Right.Once())
        {
            X += TILE_SIZE;
        }
        else if (Input.Left.Once())
        {
            X -= TILE_SIZE;
        }
    }

    void Player::Render()
    {
        MainRenderer->DrawRectangle(X, Y, TILE_SIZE, TILE_SIZE, COLOR_GREEN);
    }

} // namespace cm