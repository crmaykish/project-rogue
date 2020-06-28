#include "cm_waitaction.h"

namespace cm
{
    ActionResult WaitAction::Execute()
    {
        return ActionResult{true, "", nullptr};
    }

} // namespace cm