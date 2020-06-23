#include "cm_component_render.h"

namespace cm
{
    RenderComponent::RenderComponent(std::share_ptr<Actor> owner, std::shared_ptr<Renderer> renderer)
        : MainRenderer(renderer), Component(owner) {}

} // namespace cm