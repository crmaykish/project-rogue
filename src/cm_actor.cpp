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

        if (RenderComponent != nullptr)
        {
            RenderComponent->OnUpdate();
        }
    }

    void Actor::Render()
    {
        if (RenderComponent != nullptr)
        {
            RenderComponent->OnRender();
        }
    }

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

    void Actor::AttachMovementComponent(std::shared_ptr<Component> movementComponent)
    {
        MovementComponent = movementComponent;
    }

    void Actor::AttachRenderComponent(std::shared_ptr<Component> renderComponent)
    {
        RenderComponent = renderComponent;
    }

} // namespace cm
