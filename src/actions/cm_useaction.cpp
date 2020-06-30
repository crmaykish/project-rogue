#include "cm_useaction.h"

namespace cm
{
    UseAction::UseAction(Actor &target, int itemSlot)
        : Target(target), ItemSlot(itemSlot) {}

    ActionResult UseAction::Execute()
    {
        auto actorItems = Target.GetItems();

        if (actorItems.size() < ItemSlot)
        {
            return ActionResult{false};
        }

        auto selectedItem = actorItems.at(ItemSlot);
        selectedItem->OnUse(Target);
        
        return ActionResult{true, Target.GetName() + " used " + selectedItem->GetName()};
    }

} // namespace cm