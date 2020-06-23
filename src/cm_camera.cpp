#include "cm_camera.h"

namespace cm
{
    void Camera::SetPosition(float x, float y)
    {
        X = x;
        Y = y;
    }

    void Camera::Move(float x, float y)
    {
        X += x;
        Y += y;
    }

    float Camera::GetX()
    {
        return X;
    }

    float Camera::GetY()
    {
        return Y;
    }
}