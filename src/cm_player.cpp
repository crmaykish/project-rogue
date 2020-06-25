#include "cm_player.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input) : World(world), Input(input)
    {
        // TODO: the world should decide the player starting position
        X = 64;
        Y = 64;

        MaxHP = 100;
        HP = MaxHP;
    }

    void Player::Update()
    {
        int moveX = 0;
        int moveY = 0;

        if (Input.Right.Once())
        {
            moveX = 1;
        }
        else if (Input.Left.Once())
        {
            moveX = -1;
        }
        else if (Input.Up.Once())
        {
            moveY = 1;
        }
        else if (Input.Down.Once())
        {
            moveY = -1;
        }

        if (moveX != 0 || moveY != 0)
        {
            int tileX = (X / TileSize);
            int tileY = (Y / TileSize);
            auto targetTile = World.GetTile(tileX + moveX, tileY + moveY);

            if (targetTile.Type == TileType::Empty)
            {
                auto enemy = World.GetActor(tileX + moveX, tileY + moveY);

                if (enemy == nullptr)
                {
                    Move(moveX * TileSize, moveY * TileSize);
                }
                else
                {
                    // attack
                    enemy->Damage(10);
                }
            }
        }
    }

    void Player::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(X, Y, TileSize, TileSize, COLOR_GREEN);
    }

} // namespace cm