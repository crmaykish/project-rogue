#include "cm_map.h"
#include "cm_game_world.h"

namespace cm
{
    Tile *Map::GetTile(Point position)
    {
        if (position.X < 0 ||
            position.Y < 0 ||
            position.X >= Width ||
            position.Y >= Height)
        {
            return nullptr;
        }

        return &Tiles.at((Width * position.X) + position.Y);
    }

    std::vector<Tile *> Map::GetNeighbors(Point position, bool includeSelf)
    {
        std::vector<Tile *> neighbors;
        neighbors.reserve(9);

        if (includeSelf)
        {
            neighbors.push_back(GetTile(position));
        }

        // TODO: don't return nulls here, just add real neighbors

        neighbors.push_back(GetTile({position.X - 1, position.Y - 1}));
        neighbors.push_back(GetTile({position.X - 1, position.Y}));
        neighbors.push_back(GetTile({position.X - 1, position.Y + 1}));
        neighbors.push_back(GetTile({position.X, position.Y - 1}));
        neighbors.push_back(GetTile({position.X, position.Y + 1}));
        neighbors.push_back(GetTile({position.X + 1, position.Y - 1}));
        neighbors.push_back(GetTile({position.X + 1, position.Y}));
        neighbors.push_back(GetTile({position.X + 1, position.Y + 1}));

        return neighbors;
    }

    int Map::CountNeighborTiles(Point position, TileType type)
    {
        int neighbors = 0;
        for (auto a : GetNeighbors(position))
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
        for (auto t : TilePointers)
        {
            if (FogOfWar)
            {
                // Distance to player
                auto dist = Distance(t->Position, world.GetPlayer()->Position);

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
        for (auto t : TilePointers)
        {
            // Update fire
            if (t->OnFire > 0)
            {
                t->OnFire--;
            }

            // Update poison
            if (t->Poison > 0)
            {
                t->Poison--;
            }
        }
    }

    void Map::Render(Renderer &renderer) const
    {
        // Render world tiles
        for (auto t : TilePointers)
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
                    textureKey = t->DoorLocked ? AssetKey::DoorLockedTexture : AssetKey::DoorTexture;
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
                renderer.DrawTexture(textureKey, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);

                // Draw items or a chest if the tile contains any
                if (t->Items.size() == 1)
                {
                    renderer.DrawTexture(t->Items.at(0)->TextureKey, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);
                }
                else if (t->Items.size() > 1)
                {
                    renderer.DrawTexture(AssetKey::ChestTexture, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);
                }

                if (t->Brazier)
                {
                    renderer.DrawTexture(AssetKey::BrazierTexture, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);
                }
            }
        }
    }

    void Map::RenderPost(Renderer &renderer) const
    {
        // Render world tiles
        for (auto t : TilePointers)
        {
            if (t->Discovered)
            {
                // Draw tile effects
                if (t->OnFire > 0)
                {
                    renderer.DrawTexture(AssetKey::FireTexture, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);
                }

                if (t->Poison > 0)
                {
                    renderer.DrawTexture(AssetKey::PoisonTexture, t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize);
                }

                // Draw fog overlay
                renderer.DrawRectangle(t->Position.X * TileSize, t->Position.Y * TileSize, TileSize, TileSize,
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
