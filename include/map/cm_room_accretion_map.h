#ifndef CM_ROOM_ACCRETION_MAP_H
#define CM_ROOM_ACCRETION_MAP_H

#include "cm_map.h"

namespace cm
{
    struct Island
    {
        int X = 0;
        int Y = 0;
        int Area = 0;
    };

    class RoomAccretionMap : public Map
    {
    private:
        void BuildRoom(int x, int y, int width, int height);
        void BuildBridge(int x1, int y1, int x2, int y2);

        void RoundCorners();
        void RemoveUnknownTiles();
        std::vector<Island> FindIslands();
        void WrapWalls();

        // Return the number of tiles connected to this one
        int FloodFill(int x, int y);

    public:
        void Generate() override;
    };
} // namespace cm

#endif /* CM_ROOM_ACCRETION_MAP_H */
