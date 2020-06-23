#include "cm_component_render.h"

namespace cm
{
    RenderComponent::RenderComponent(std::shared_ptr<Renderer> renderer)
        : MainRenderer(renderer) {}

} // namespace cm