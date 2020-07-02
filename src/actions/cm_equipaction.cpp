#include "cm_equipaction.h"
#include "cm_actor.h"

namespace cm
{
    EquipAction::EquipAction(int itemSlot) : ItemSlot(itemSlot) {}

    ActionResult EquipAction::Execute(Actor &executor)
    {
        auto itemName = executor.GetInventory()->ItemAt(ItemSlot)->Name;

        executor.GetInventory()->EquipItem(ItemSlot);

        return ActionResult(ActionStatus::Succeeded, executor.Name + " equipped " + itemName);
    }

} // namespace cm