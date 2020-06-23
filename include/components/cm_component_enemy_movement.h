#include "cm_component.h"
#include "cm_actor.h"
#include "cm_input.h"

namespace cm
{
    class EnemyMovementComponent : public Component
    {
    private:
        std::shared_ptr<Actor> Enemy;

    public:
        // TODO: this will probably need to take in a game world or something
        EnemyMovementComponent(std::shared_ptr<Actor> enemy);
        void OnUpdate() override;
        void OnRender() override;
    };

} // namespace cm
