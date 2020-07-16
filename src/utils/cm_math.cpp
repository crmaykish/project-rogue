#include "cm_math.h"

namespace cm
{
    int Distance(Point a, Point b)
    {
        int xDist = std::abs(a.X - b.X);
        int yDist = std::abs(a.Y - b.Y);
        return std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
    }
} // namespace cm
