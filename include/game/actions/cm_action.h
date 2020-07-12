#ifndef CM_ACTION_H
#define CM_ACTION_H

#include <memory>
#include <string>

namespace cm
{
    // Forward declarations
    class Actor;
    struct ActionResult;

    /**
     * @brief When an [Action] is executed on an [Actor], it may succeed or fail for various reasons.
     * This captures the possible outcome status of executing an [Action].
     */
    enum struct ActionStatus
    {
        Unknown,   // Unknown result
        Waiting,   // Action requires further input before completing
        Succeeded, // Action succeeded as intended
        Failed,    // Action was valid, but failed to complete
        Invalid,   // Action requested with invalid parameters
        Alternate  // Alternate action suggested
    };

    /**
     * @brief An [Action] is something that an [Actor] can attempt to do
     */
    class Action
    {
    public:
        virtual ~Action() {}
        virtual ActionResult Execute(Actor &executor) = 0;
        virtual void SetTarget(int x, int y) {}
    };

    class ActionResult
    {
    public:
        ActionStatus Status = ActionStatus::Unknown;
        std::string Message;
        std::unique_ptr<Action> AlternateAction;

        ActionResult(ActionStatus status);
        ActionResult(ActionStatus status, std::string message);
        ActionResult(std::unique_ptr<Action> alternateAction);
    };

} // namespace cm

#endif // CM_ACTION_H
