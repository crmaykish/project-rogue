#include "cm_waitaction.h"
#include "cm_actor.h"

namespace cm
{
    ActionResult WaitAction::Execute(Actor &executor)
    {
        if (executor.Friendly)
        {
            return ActionResult(ActionStatus::Succeeded, executor.Name + " is waiting");
        }
        else
        {
            return ActionResult(ActionStatus::Succeeded);
        }
    }

} // namespace cm