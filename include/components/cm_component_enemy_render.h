#ifndef CM_COMPONENT_ENEMY_RENDER_H
#define CM_COMPONENT_ENEMY_RENDER_H

#include "cm_component_render.h"
#include "cm_actor.h"

namespace cm
{
    class EnemyRenderComponent : public RenderComponent
    {
    private:
        std::shared_ptr<Actor> Enemy;

    public:
        EnemyRenderComponent(std::shared_ptr<Actor> enemy, std::shared_ptr<Renderer> renderer);
        void OnUpdate() override;
        void OnRender() override;
    };
} // namespace cm

#endif // CM_COMPONENT_ENEMY_RENDER_H
