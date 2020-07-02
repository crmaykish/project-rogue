#include "cm_useaction.h"
#include "cm_actor.h"

namespace cm
{
    UseAction::UseAction(int itemSlot) : ItemSlot(itemSlot) {}

    ActionResult UseAction::Execute(Actor &executor)
    {
        auto item = executor.GetInventory()->ItemAt(ItemSlot);

        if (item == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, "No item in slot: " + std::to_string(ItemSlot));
        }

        item->Use(executor);

        if (item->Charges == 0)
        {
            executor.GetInventory()->RemoveItem(ItemSlot);
        }

        return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + item->Name);
    }

} // namespace cm