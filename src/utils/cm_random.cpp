#include "cm_random.h"

namespace cm
{
    int RandomInt(int max)
    {
        return rand() % max;
    }
}