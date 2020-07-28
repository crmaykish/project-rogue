#ifndef CM_MAP_H
#define CM_MAP_H

#include <memory>
#include <vector>
#include "cm_tile.h"
#include "cm_renderer.h"
#include "cm_actor.h"

namespace cm
{
    const int MaxWidth = 1000;
    const int MaxHeight = 1000;
    const int MaxTiles = MaxWidth * MaxHeight;

    class GameWorld;

    class Map
    {
    protected:
        int Width = 0;
        int Height = 0;
        int PlayerX = 0;
        int PlayerY = 0;

        // std::vector<std::unique_ptr<Tile>> Tiles;
        std::array<Tile, MaxTiles> Tiles;

        // TODO: i'm not sure this has made any difference in performance


        std::vector<Tile *> TilePointers;

        // TODO: store a vector of pointers to active tiles. Is that faster than looping through the array and checking for active?

        // TODO: this should probably just be a lambda
        int CountNeighborTiles(Point position, TileType type);

    public:
        virtual ~Map() {}
        virtual void Generate() = 0;
        virtual std::vector<std::unique_ptr<Actor>> SpawnNPCs(int playerLevel) = 0;

        void Update(GameWorld &world);
        void Tick(GameWorld &world);
        void Render(Renderer &renderer) const;
        void RenderPost(Renderer &renderer) const;

        int GetWidth() const;
        int GetHeight() const;

        int GetPlayerX() const;
        int GetPlayerY() const;

        Tile *GetTile(Point position);
        std::vector<Tile *> GetNeighbors(Point position, bool includeSelf = false);
    };

} // namespace cm

#endif /* CM_MAP_H */
