#include "cm_exitlevelaction.h"

namespace cm
{
    ExitLevelAction::ExitLevelAction(GameWorld &world) : World(world) {}

    ActionResult ExitLevelAction::Execute(Actor &executor)
    {
        World.SetNextLevel();

        return ActionResult(ActionStatus::Succeeded);
    }

} // namespace cm