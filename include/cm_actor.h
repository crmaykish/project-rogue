#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_renderer.h"
#include "cm_component.h"

namespace cm
{
    class Actor
    {
    protected:
        float X = 0;
        float Y = 0;

        std::shared_ptr<Component> MovementComponent = nullptr;

    public:
        Actor(float x, float y);

        void Update();
        void Render(std::shared_ptr<Renderer>);

        void Move(float x, float y);

        void AttachMovementComponent(std::shared_ptr<Component> movementComponent);
    };

} // namespace cm

#endif // CM_ACTOR_H
