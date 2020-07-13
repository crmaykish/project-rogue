#ifndef CM_ROOM_ACCRETION_MAP_H
#define CM_ROOM_ACCRETION_MAP_H

#include "cm_map.h"

namespace cm
{
    struct Island;

    class RoomAccretionMap : public Map
    {
    private:
        void BuildRoom(int x, int y, int width, int height);
        void BuildBridge(int x1, int y1, int x2, int y2);

        void RoundCorners();
        void RemoveUnknownTiles();
        void WrapWalls();
        void PlaceExit();
        void PlacePlayer();
        void PlaceTreasure();
        std::vector<Island> FindIslands();

        // Return the number of tiles connected to this one
        int FloodFill(int x, int y);

    public:
        void Generate() override;
        std::vector<std::unique_ptr<Actor>> SpawnNPCs() override;
    };
} // namespace cm

#endif /* CM_ROOM_ACCRETION_MAP_H */
