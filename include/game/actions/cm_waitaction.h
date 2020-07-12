#ifndef CM_WAITACTION_H
#define CM_WAITACTION_H

#include "cm_action.h"

namespace cm
{
    class WaitAction : public Action
    {
    public:
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_WAITACTION_H
