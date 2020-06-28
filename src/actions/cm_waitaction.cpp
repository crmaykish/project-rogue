#include "cm_waitaction.h"

namespace cm
{
    WaitAction::WaitAction(Actor &target, GameWorld &world)
        : Target(target), World(world) {}

    ActionResult WaitAction::Execute()
    {
        return ActionResult{true, Target.GetName() + " is waiting", nullptr};
    }

} // namespace cm