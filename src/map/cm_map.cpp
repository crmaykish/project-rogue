#include "cm_map.h"
#include "cm_game_world.h"

namespace cm
{
    Tile *Map::GetTile(int x, int y) const
    {
        if (x < 0 || x >= Width || y < 0 || y >= Height)
        {
            return nullptr;
        }

        for (auto const &t : Tiles)
        {
            if (t->X == x && t->Y == y)
            {
                return t.get();
            }
        }

        return nullptr;
    }

    std::vector<Tile *> Map::GetNeighbors(int x, int y) const
    {
        std::vector<Tile *> neighbors;

        // TODO: This is amazingly inefficient
        neighbors.push_back(GetTile(x - 1, y - 1));
        neighbors.push_back(GetTile(x - 1, y));
        neighbors.push_back(GetTile(x - 1, y + 1));
        neighbors.push_back(GetTile(x, y - 1));
        neighbors.push_back(GetTile(x, y + 1));
        neighbors.push_back(GetTile(x + 1, y - 1));
        neighbors.push_back(GetTile(x + 1, y));
        neighbors.push_back(GetTile(x + 1, y + 1));

        return neighbors;
    }

    int Map::CountNeighborTiles(int x, int y, TileType type)
    {
        int neighbors = 0;
        for (auto a : GetNeighbors(x, y))
        {
            if (a != nullptr)
            {
                if (a->Type == type)
                {
                    neighbors++;
                }
            }
        }
        return neighbors;
    }

    void Map::Update(GameWorld &world)
    {
        for (auto &t : Tiles)
        {
            // Distance to player
            auto dist = Distance({t->X, t->Y}, world.GetPlayer()->Position);

            int offset = (world.GetPlayer()->TorchFuel + 1) / 5;

            if (dist <= offset + 1)
            {
                t->Brightness = 0xFF;
            }
            if (dist == offset + 2)
            {
                t->Brightness = 0xC0;
            }
            if (dist == offset + 3)
            {
                t->Brightness = 0xA0;
            }
            if (dist == offset + 4)
            {
                t->Brightness = 0x60;
            }

            if (t->Brightness > 0)
            {
                t->Discovered = true;
            }
        }
    }

    void Map::Render(Renderer &renderer) const
    {
        // Render world tiles
        for (auto &t : Tiles)
        {
            // TODO: should be a switch
            if (t->Type == TileType::Wall)
            {
                renderer.DrawTexture(AssetKey::WallTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::WallCracked)
            {
                renderer.DrawTexture(AssetKey::WallCrackedTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Empty)
            {
                renderer.DrawTexture(AssetKey::FloorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Door)
            {
                renderer.DrawTexture(AssetKey::DoorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Water)
            {
                renderer.DrawTexture(AssetKey::WaterTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Bridge)
            {
                renderer.DrawTexture(AssetKey::BridgeTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else
            {
                // Unrecognized tile type
                renderer.DrawTexture(AssetKey::Unknown, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }

            if (t->Items.size() == 1)
            {
                renderer.DrawTexture(t->Items.at(0)->GetTextureKey(), t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Items.size() > 1)
            {
                renderer.DrawTexture(AssetKey::ChestTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }

            // draw fog
            Color overlayColor = ColorBlack;

            if (t->Brightness == 0 && t->Discovered)
            {
                overlayColor.alpha = 0xFF - 0x20;
            }
            else
            {
                overlayColor.alpha = 0xFF - t->Brightness;
            }

            renderer.DrawRectangle(t->X * TileSize, t->Y * TileSize, TileSize, TileSize, overlayColor);
        }
    }

    int Map::GetWidth() const
    {
        return Width;
    }

    int Map::GetHeight() const
    {
        return Height;
    }

    int Map::GetPlayerX() const
    {
        return PlayerX;
    }

    int Map::GetPlayerY() const
    {
        return PlayerY;
    }

} // namespace cm
