#include "cm_useaction.h"

namespace cm
{
    UseAction::UseAction(int itemSlot) : ItemSlot(itemSlot) {}

    ActionResult UseAction::Execute(Actor &executor)
    {
        return ActionResult(ActionStatus::Invalid);
    }

} // namespace cm