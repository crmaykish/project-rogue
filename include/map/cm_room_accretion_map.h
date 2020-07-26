#ifndef CM_ROOM_ACCRETION_MAP_H
#define CM_ROOM_ACCRETION_MAP_H

#include "cm_map.h"

namespace cm
{
    struct Island;

    class RoomAccretionMap : public Map
    {
    protected:
        void BuildRoom(int x, int y, int width, int height);
        void BuildBridge(int x1, int y1, int x2, int y2);

        void RoundCorners();
        void RemoveUnknownTiles();
        void WrapWalls();
        void PlaceExit();
        void PlacePlayer();
        void PlaceTreasure();
        void FloodOpenAreas();
        std::vector<Island> FindIslands();

        /**
         * @brief Count the number of tiles connected to the tile at [x, y]
         */
        int FloodFill(int x, int y);

        /**
         * @brief Return a random tile of the given type or nullptr if no tile is found of that type
         */
        Tile *RandomTile(TileType type);

    public:
        void Generate() override;
        std::vector<std::unique_ptr<Actor>> SpawnNPCs(int playerLevel) override;
    };
} // namespace cm

#endif /* CM_ROOM_ACCRETION_MAP_H */
