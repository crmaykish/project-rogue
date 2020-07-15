#ifndef CM_RANDOM_H
#define CM_RANDOM_H

#include <cstdlib>

// TODO: replace this lib with c++11 random tools

namespace cm
{
    /**
     * @brief Return a random integer between 0 (inclusive) and max (exclusive)
     */
    int RandomInt(int max);

    /**
     * @brief Return a random integer between min and max inclusive
     */
    int RandomInt(int min, int max);

    /**
     * @brief Return true or false at random
     */
    int RandomBool();

    /**
     * @brief Return true randomly at the given percentage
     * e.g. RandomPercentCheck(20) will return true 20% of the time and false 80%
     */
    bool RandomPercentCheck(int percent);

} // namespace cm

#endif // CM_RANDOM_H
