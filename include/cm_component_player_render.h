#ifndef CM_COMPONENT_PLAYER_RENDER_H
#define CM_COMPONENT_PLAYER_RENDER_H

#include <memory>
#include "cm_component_render.h"
#include "cm_renderer.h"

namespace cm
{
    class PlayerRenderComponent : public RenderComponent
    {
    private:
        std::shared_ptr<Renderer> MainRenderer;

    public:
        PlayerRenderComponent(std::shared_ptr<Actor> player, std::shared_ptr<Renderer> renderer);
        void OnUpdate() override;
        void OnRender() override;
    };

} // namespace cm

#endif // CM_COMPONENT_PLAYER_RENDER_H
