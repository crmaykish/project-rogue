#include "cm_equipaction.h"
#include "cm_actor.h"

namespace cm
{
    EquipAction::EquipAction(int itemSlot) : ItemSlot(itemSlot) {}

    ActionResult EquipAction::Execute(Actor &executor)
    {
        auto itemName = executor.InventoryComp->ItemAt(ItemSlot)->DisplayName();

        executor.InventoryComp->EquipItem(ItemSlot);

        return ActionResult(ActionStatus::Succeeded, executor.Name + " equipped " + itemName);
    }

} // namespace cm