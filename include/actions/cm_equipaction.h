#ifndef CM_EQUIPACTION_H
#define CM_EQUIPACTION_H

#include "cm_action.h"

namespace cm
{
    class EquipAction : public Action
    {
    private:
        int ItemSlot;

    public:
        EquipAction(int itemSlot);
        ActionResult Execute(Actor &executor) override;
    };
} // namespace cm

#endif // CM_EQUIPACTION_H
