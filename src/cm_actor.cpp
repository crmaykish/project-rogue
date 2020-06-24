#include "cm_actor.h"

namespace cm
{
    void Actor::Move(float x, float y)
    {
        X += x;
        Y += y;
    }

    float Actor::GetX()
    {
        return X;
    }

    float Actor::GetY()
    {
        return Y;
    }

} // namespace cm
