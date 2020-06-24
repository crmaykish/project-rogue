#ifndef CM_WORLD_H
#define CM_WORLD_H

#include <vector>
#include <memory>
#include "cm_renderer.h"

namespace cm
{
    const int TILE_SIZE = 32;

    struct Tile
    {
        // TODO: a tile will probably need to store some kind of reference to actors it contains, even if it doesn't own them
        int X = 0;
        int Y = 0;
        bool Walkable = true;
        bool NullTile = false; // hack
    };

    class World
    {
    private:
        std::vector<Tile> Map;
        int Turn = 1;

    public:
        static std::unique_ptr<World> GenerateWorld(int width, int height);

        void Update();
        void Step();
        void Render(Renderer &renderer);

        Tile TileAt(int x, int y);
    };
} // namespace cm

#endif // CM_WORLD_H
