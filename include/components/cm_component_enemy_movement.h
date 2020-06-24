#include "cm_component.h"
#include "cm_actor.h"
#include "cm_world.h"

namespace cm
{
    class EnemyMovementComponent : public Component
    {
    private:
        std::shared_ptr<Actor> Enemy;
        std::shared_ptr<World> GameWorld;

        int Direction = 1;

    public:
        // TODO: this will probably need to take in a game world or something
        EnemyMovementComponent(std::shared_ptr<Actor> enemy, std::shared_ptr<World> gameWorld);
        void OnUpdate() override;
        void OnRender() override;
    };

} // namespace cm
