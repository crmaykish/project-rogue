#include "cm_random.h"

namespace cm
{
    int RandomInt(int max)
    {
        return rand() % max;
    }

    int RandomInt(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    int RandomBool()
    {
        return RandomInt(2) == 0;
    }

    bool RandomPercentCheck(int percent)
    {
        return RandomInt(100) < percent;
    }
}