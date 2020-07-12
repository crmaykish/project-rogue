#include "cm_map.h"

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

    void Map::Render(Renderer &renderer)
    {
        // Render world tiles
        for (auto &t : Tiles)
        {
            if (t->Type == TileType::Wall)
            {
                renderer.DrawTexture(AssetKey::WallTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Empty)
            {
                renderer.DrawTexture(AssetKey::FloorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }
            else if (t->Type == TileType::Door)
            {
                renderer.DrawTexture(AssetKey::DoorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
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
