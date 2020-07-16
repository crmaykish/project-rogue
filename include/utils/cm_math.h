#ifndef CM_MATH_H
#define CM_MATH_H

#include <math.h>

namespace cm
{
    struct Point
    {
        int X = 0;
        int Y = 0;
    };

    int Distance(Point a, Point b);

} // namespace cm

#endif // CM_MATH_H
