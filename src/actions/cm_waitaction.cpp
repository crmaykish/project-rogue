#include "cm_waitaction.h"
#include "cm_actor.h"

namespace cm
{
    ActionResult WaitAction::Execute(Actor &executor)
    {
        return ActionResult(ActionStatus::Succeeded, executor.GetName() + " is waiting");
    }

} // namespace cm