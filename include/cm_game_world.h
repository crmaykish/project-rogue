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
        int TurnCount = 0;
        int Width = 0;
        int Height = 0;
        int CurrentActorIndex = 0;
        std::vector<std::unique_ptr<Tile>> Tiles;
        std::vector<std::shared_ptr<Actor>> Actors;
        std::shared_ptr<Actor> PlayerOne;

        void CreateLevel();

        // Return the actor whose turn it is
        Actor *GetCurrentActor();
        void NextActor();

    public:
        int ViewDistance = 4;

        GameWorld();

        void Init();

        void Update();
        void Render(Renderer &renderer);

        void AddPlayer(std::shared_ptr<Actor> player);

        Tile *GetTile(int x, int y) const;
        Actor *GetActor(int x, int y) const;

        Actor *GetPlayer() const;

        int DistanceToPlayer(int x, int y) const;

        int GetWidth();
        int GetHeight();

        void SetNextLevel();

        bool IsTileVisible(int x, int y) const;
    };

} // namespace cm

#endif // CM_WORLD_H
