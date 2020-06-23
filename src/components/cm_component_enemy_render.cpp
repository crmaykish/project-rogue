#ifndef CM_COMPONENET_ENEMY_RENDER_H
#define CM_COMPONENET_ENEMY_RENDER_H

#include "cm_component_enemy_render.h"
#include "cm_world.h"

namespace cm
{
    EnemyRenderComponent::EnemyRenderComponent(std::shared_ptr<Actor> Enemy, std::shared_ptr<Renderer> renderer)
        : Enemy(Enemy), RenderComponent(renderer) {}

    void EnemyRenderComponent::OnUpdate() {}

    void EnemyRenderComponent::OnRender()
    {
        float EnemyOffset = 4;
        float EnemySize = TILE_SIZE - 2 * EnemyOffset;

        MainRenderer->DrawRectangle(Enemy->GetX() + EnemyOffset,
                                    Enemy->GetY() + EnemyOffset,
                                    EnemySize,
                                    EnemySize,
                                    COLOR_RED);
    }

} // namespace cm

#endif // CM_COMPONENET_ENEMY_RENDER_H