#include "cm_player.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input) : World(world), Input(input)
    {
        // TODO: the world should decide the player starting position
        TileX = 2;
        TileY = 2;

        MaxHP = 100;
        HP = MaxHP;

        Active = true;
        Visible = true;
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
            auto targetTile = World.GetTile(TileX + moveX, TileY + moveY);

            if (targetTile.Type == TileType::Empty)
            {
                auto enemy = World.GetActor(TileX + moveX, TileY + moveY);

                if (enemy == nullptr)
                {
                    Move(moveX, moveY);
                }
                else
                {
                    // attack
                    enemy->Damage(10);

                    if (!enemy->IsActive())
                    {
                        Move(moveX, moveY);
                    }
                }
            }
        }
    }

    void Player::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(TileX * TileSize, TileY * TileSize, TileSize, TileSize, COLOR_GREEN);
    }

} // namespace cm