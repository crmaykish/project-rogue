#ifndef CM_WAITACTION_H
#define CM_WAITACTION_H

#include "cm_action.h"

namespace cm
{
    class WaitAction : public Action
    {
    private:
    public:
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_WAITACTION_H
