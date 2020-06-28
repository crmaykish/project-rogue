#ifndef CM_ATTACKACTION_H
#define CM_ATTACKACTION_H

#include "cm_action.h"

namespace cm
{
    class AttackAction : public Action
    {
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_ATTACKACTION_H
