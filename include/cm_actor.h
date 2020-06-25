#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>

#include "cm_renderer.h"

namespace cm
{
    class Actor
    {
    protected:
        float X = 0;
        float Y = 0;
        bool Active;

    public:
        virtual ~Actor() {}
        virtual void Update() = 0;
        virtual void Render(Renderer &renderer) = 0;
        float GetX();
        float GetY();
        void Move(float x, float y);

        bool IsActive();
    };

} // namespace cm

#endif // CM_ACTOR_H
