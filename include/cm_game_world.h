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
        int Width = 0;
        int Height = 0;
        std::vector<Tile> Tiles;
        std::vector<std::shared_ptr<Actor>> Actors;
        std::shared_ptr<Actor> PlayerOne;

    public:
        GameWorld(int x, int y);
        void Step();
        void Update();
        void Render(Renderer &renderer);

        void AddActor(std::shared_ptr<Actor> actor);
        void AddPlayer(std::shared_ptr<Actor> player);

        const Tile GetTile(int x, int y);
        std::shared_ptr<Actor> GetActor(int x, int y);

        const Actor &GetPlayer();

        int GetWidth();
        int GetHeight();
    };

} // namespace cm

#endif // CM_WORLD_H
