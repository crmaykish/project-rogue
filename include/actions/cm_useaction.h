#ifndef CM_USEACTION_H
#define CM_USEACTION_H

#include "cm_action.h"
#include "cm_actor.h"

namespace cm
{
    class UseAction : public Action
    {
    private:
        Actor &Target;
        int ItemSlot = 0;

    public:
        UseAction(Actor &target, int itemSlot);
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_USEACTION_H
