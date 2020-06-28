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
        bool NextLevel = false;
        int LevelIndex = 0;
        int Width = 0;
        int Height = 0;
        int CurrentActorIndex = 0;
        std::vector<Tile> Tiles;
        std::vector<std::shared_ptr<Actor>> Actors;
        std::shared_ptr<Actor> PlayerOne;

        int ViewDistance = 4;

        void CreateLevel();

    public:
        GameWorld();

        void Init();

        void Update();
        void Render(Renderer &renderer);

        void AddActor(std::shared_ptr<Actor> actor);
        void AddPlayer(std::shared_ptr<Actor> player);

        const Tile GetTile(int x, int y);
        std::shared_ptr<Actor> GetActor(int x, int y);

        Actor &GetPlayer();

        int DistanceToPlayer(int x, int y);

        int GetViewDistance();

        int GetWidth();
        int GetHeight();

        void SetNextLevel();

        int GetLevelIndex();
    };

} // namespace cm

#endif // CM_WORLD_H
