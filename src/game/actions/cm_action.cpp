#include "cm_action.h"

namespace cm
{
    ActionResult::ActionResult(ActionStatus status)
        : Status(status) {}

    ActionResult::ActionResult(ActionStatus status, std::string message)
        : Status(status), Message(message) {}

    ActionResult::ActionResult(std::unique_ptr<Action> alternateAction)
        : Status(ActionStatus::Alternate), AlternateAction(std::move(alternateAction)) {}

} // namespace cm