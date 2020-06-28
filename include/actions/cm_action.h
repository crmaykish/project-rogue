#ifndef CM_ACTION_H
#define CM_ACTION_H

#include <memory>

namespace cm
{
    struct ActionResult;

    class Action
    {
    public:
        virtual ActionResult Execute() = 0;
    };

    struct ActionResult
    {
        bool Success = false;
        std::string Message;
        std::shared_ptr<Action> AlternateAction = nullptr;
    };

} // namespace cm

#endif // CM_ACTION_H
