#ifndef CM_PATHFINDER_H
#define CM_PATHFINDER_H

#include "cm_math.h"
#include "cm_game_world.h"

namespace cm
{
    class Pathfinder
    {
    public:
        /**
         * @brief Find and return a path from the starting point to the destination using
         * a breadth-first search algorithm
         * 
         * @param world Reference to the game world
         * @param start Coordinates of the starting position
         * @param destination Coordinates of the goal position
         * @return std::vector<Point> A sorted list of coordinates representing a path from start to destination
         */
        static std::vector<Point> Path(GameWorld &world, Point start, Point destination);
    };
} // namespace cm

#endif /* CM_PATHFINDER_H */
