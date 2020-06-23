#include "cm_component_enemy_movement.h"
#include "cm_world.h"

namespace cm
{
    EnemyMovementComponent::EnemyMovementComponent(std::shared_ptr<Actor> enemy) : Enemy(enemy) {}

    void EnemyMovementComponent::OnUpdate()
    {
        if (Enemy->GetX() < 800)
        {
            Enemy->Move(0.2, 0.0);
        }
    }

    void EnemyMovementComponent::OnRender()
    {
    }

} // namespace cm