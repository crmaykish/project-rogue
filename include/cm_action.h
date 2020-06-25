#ifndef CM_ACTION_H
#define CM_ACTION_H

namespace cm
{
    enum struct ActionResult
    {
        Success,
        Failure
    };

    class Action
    {
    public:
        virtual ActionResult Execute() = 0;
    };

} // namespace cm

#endif // CM_ACTION_H
