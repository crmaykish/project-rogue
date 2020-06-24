#ifndef CM_WORLD_H
#define CM_WORLD_H

#include <vector>
#include "cm_tile.h"
#include "cm_actor.h"
#include "cm_renderer.h"

namespace cm
{
    class GameWorld
    {
    private:
        std::vector<Tile> Tiles;
        std::vector<std::unique_ptr<Actor>> Actors;

    public:
        GameWorld(int x, int y);
        void Step();
        // void Update();
        void Render(Renderer &renderer);

        void AddActor(std::unique_ptr<Actor> actor);
    };

} // namespace cm

#endif // CM_WORLD_H
