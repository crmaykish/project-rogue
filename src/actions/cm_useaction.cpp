#include "cm_useaction.h"

namespace cm
{
    UseAction::UseAction(Actor &target, int itemSlot)
        : Target(target), ItemSlot(itemSlot) {}

    ActionResult UseAction::Execute()
    {
        ActionResult result;

        auto item = Target.GetItems().at(ItemSlot);

        item->OnUse(Target);

        result.Message = Target.GetName() + " used " + Target.GetItems().at(ItemSlot)->GetName();

        result.Success = true;

        return result;
    }

} // namespace cm