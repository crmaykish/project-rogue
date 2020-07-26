#include "cm_map.h"
#include "cm_game_world.h"

namespace cm
{
    // TODO: I think this function is a huge bottleneck
    // Switch to a PointMap for storing tiles? Makes iterating slightly harder, but looks up are way faster
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

    std::vector<Tile *> Map::GetNeighbors(int x, int y, bool includeSelf) const
    {
        std::vector<Tile *> neighbors;

        // TODO: This is amazingly inefficient

        if (includeSelf)
        {
            neighbors.push_back(GetTile(x, y));
        }

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
        // TODO: this doesn't need to run at the full framerate. only when something moves
        for (auto &t : Tiles)
        {
            if (FogOfWar)
            {
                // Distance to player
                auto dist = Distance({t->X, t->Y}, world.GetPlayer()->Position);

                if (dist <= world.GetPlayer()->Stats.ViewDistance())
                {
                    t->Brightness = TileBrightnessMax - (TileBrightnessInterval * dist);
                    t->Discovered = true;
                }
                else
                {
                    t->Brightness = TileBrightnessMin;
                }
            }
        }
    }

    void Map::Tick(GameWorld &world)
    {
        for (auto &t : Tiles)
        {
            // Update fire
            if (t->OnFire > 0)
            {
                t->OnFire--;
            }
        }
    }

    void Map::Render(Renderer &renderer) const
    {
        // Render world tiles
        for (auto &t : Tiles)
        {
            if (t->Discovered)
            {
                // TODO: should tiles render themselves?

                auto textureKey = AssetKey::Unknown;

                switch (t->Type)
                {
                case TileType::Wall:
                    textureKey = AssetKey::WallTexture;
                    break;
                case TileType::Floor:
                    textureKey = AssetKey::FloorTexture;
                    break;
                case TileType::Door:
                    textureKey = AssetKey::DoorTexture;
                    break;
                case TileType::Water:
                    textureKey = AssetKey::WaterTexture;
                    break;
                case TileType::Bridge:
                    textureKey = AssetKey::BridgeTexture;
                    break;
                default:
                    break;
                }

                // Draw the tile
                renderer.DrawTexture(textureKey, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);

                // Draw items or a chest if the tile contains any
                if (t->Items.size() == 1)
                {
                    renderer.DrawTexture(t->Items.at(0)->TextureKey, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }
                else if (t->Items.size() > 1)
                {
                    renderer.DrawTexture(AssetKey::ChestTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }

                if (t->Brazier)
                {
                    renderer.DrawTexture(AssetKey::BrazierTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }
            }
        }
    }

    void Map::RenderPost(Renderer &renderer) const
    {
        // Render world tiles
        for (auto &t : Tiles)
        {
            if (t->Discovered)
            {
                // Draw tile effects
                if (t->OnFire > 0)
                {
                    renderer.DrawTexture(AssetKey::FireTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }

                // Draw fog overlay
                renderer.DrawRectangle(t->X * TileSize, t->Y * TileSize, TileSize, TileSize,
                                       Color{ColorBlack.red, ColorBlack.green, ColorBlack.blue, static_cast<uint8_t>(TileBrightnessMax - t->Brightness)});
            }
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
