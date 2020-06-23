#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_component.h"

namespace cm
{
    class Actor
    {
    protected:
        float X = 0;
        float Y = 0;

        std::shared_ptr<Component> MovementComponent = nullptr;
        std::shared_ptr<Component> RenderComponent = nullptr;

    public:
        Actor(float x, float y);

        void Update();
        void Render();

        float GetX();
        float GetY();

        void Move(float x, float y);

        void AttachMovementComponent(std::shared_ptr<Component> movementComponent);
        void AttachRenderComponent(std::shared_ptr<Component> renderComponent);
    };

} // namespace cm

#endif // CM_ACTOR_H
