#ifndef CM_USEACTION_H
#define CM_USEACTION_H

#include "cm_action.h"

namespace cm
{
    class UseAction : public Action
    {
    private:
        int ItemSlot = 0;

    public:
        UseAction(int itemSlot);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_USEACTION_H
