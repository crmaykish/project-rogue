#include "cm_waitaction.h"

namespace cm
{
    ActionResult WaitAction::Execute(Actor &executor)
    {
        return ActionResult(ActionStatus::Succeeded, executor.GetName() + " is waiting");
    }

} // namespace cm