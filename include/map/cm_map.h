#ifndef CM_MAP_H
#define CM_MAP_H

#include <memory>
#include <vector>
#include "cm_tile.h"
#include "cm_renderer.h"

namespace cm
{
    class Map
    {
    protected:
        int Width = 0;
        int Height = 0;
        int PlayerX = 0;
        int PlayerY = 0;

        std::vector<std::unique_ptr<Tile>> Tiles;

        // TODO: this should probably just be a lambda
        int CountNeighborTiles(int x, int y, TileType type);

    public:
        virtual ~Map() {}
        virtual void Generate() = 0;

        // TODO: Need another method to return a list of enemies

        void Render(Renderer &renderer);

        int GetWidth() const;
        int GetHeight() const;

        int GetPlayerX() const;
        int GetPlayerY() const;

        Tile *GetTile(int x, int y) const;
        std::vector<Tile *> GetNeighbors(int x, int y) const;
    };

} // namespace cm

#endif /* CM_MAP_H */
