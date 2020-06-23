#ifndef CM_COMPONENT_RENDER_H
#define CM_COMPONENT_RENDER_H

#include <memory>
#include "cm_component.h"
#include "cm_renderer.h"

namespace cm
{
    class RenderComponent : public Component
    {
    protected:
        std::shared_ptr<Renderer> MainRenderer;

    public:
        RenderComponent(std::shared_ptr<Renderer> renderer);
    };
} // namespace cm

#endif // CM_COMPONENT_RENDER_H
