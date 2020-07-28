#ifndef CM_MAP_H
#define CM_MAP_H

#include <memory>
#include <vector>
#include "cm_tile.h"
#include "cm_renderer.h"
#include "cm_actor.h"

namespace cm
{
    const int MaxWidth = 100;
    const int MaxHeight = 100;
    const int MaxTiles = MaxWidth * MaxHeight;

    class GameWorld;

    class Map
    {
    protected:
        int Width = 0;
        int Height = 0;
        int PlayerX = 0;
        int PlayerY = 0;

        std::array<Tile, MaxTiles> Tiles;

        // TODO: i'm not sure this has made any difference in performance
        std::vector<Tile *> TilePointers;

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

        /**
         * @brief Return a list of non-null pointers to any neighboring tiles
         * 
         * @param position Point at which to find neighbors
         * @param includeSelf Include the tile at position in the return vector
         * @return std::vector<Tile *> A vector of pointers to neighboring tiles
         */
        std::vector<Tile *> GetNeighbors(Point position, bool includeSelf = false);
    };

} // namespace cm

#endif /* CM_MAP_H */
