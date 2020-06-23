#include "cm_actor.h"

namespace cm
{
    Actor::Actor(float x, float y) : X(x), Y(y) {}

    void Actor::Update()
    {
        if (MovementComponent != nullptr)
        {
            MovementComponent->OnUpdate();
        }
    }

    void Actor::Render(std::shared_ptr<Renderer> renderer)
    {
        renderer->DrawRectangle(X, Y, 64, 64, COLOR_GREEN);
    }

    void Actor::Move(float x, float y)
    {
        X += x;
        Y += y;
    }

    void Actor::AttachMovementComponent(std::shared_ptr<Component> movementComponent)
    {
        MovementComponent = movementComponent;
    }

} // namespace cm
