#include <queue>
#include <algorithm>
#include "cm_containers.h"
#include "cm_pathfinder.h"

namespace cm
{
    std::vector<Point> Pathfinder::Path(GameWorld &world, Point start, Point destination)
    {
        // TODO: handle paths blocked by other enemies, etc

        std::vector<Point> path;
        std::queue<Point> frontier;
        cm::CoordinateMap<Point> cameFrom;
        Point current;

        frontier.push(start);

        while (!frontier.empty())
        {
            current = frontier.front();
            frontier.pop();

            if (current == destination)
            {
                break;
            }

            for (auto next : world.GetLevel()->GetNeighbors(current.X, current.Y))
            {
                if (next != nullptr && next->Walkable)
                {
                    auto p = Point{next->X, next->Y};
                    if (!cameFrom.Contains(p.X, p.Y))
                    {
                        frontier.push(p);
                        cameFrom.Insert(p.X, p.Y, current);
                    }
                }
            }
        }

        // TODO: if there is no path from start to destination, this will probably crash
        while (current != start)
        {
            path.push_back(current);
            current = *(cameFrom.At(current.X, current.Y));
        }

        std::reverse(path.begin(), path.end());

        return path;
    }

} // namespace cm