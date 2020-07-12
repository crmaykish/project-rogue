#include "cm_useaction.h"
#include "cm_equipaction.h"
#include "cm_actor.h"

namespace cm
{
    UseAction::UseAction(int itemSlot) : ItemSlot(itemSlot) {}

    ActionResult UseAction::Execute(Actor &executor)
    {
        auto item = executor.GetInventory()->ItemAt(ItemSlot - 1);

        if (item == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, "No item in slot: " + std::to_string(ItemSlot));
        }

        if (item->Type == ItemType::Consumable)
        {
            // Use the item
            item->Use(executor);

            if (item->Charges == 0)
            {
                executor.GetInventory()->RemoveItem(ItemSlot - 1);
            }

            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + item->DisplayName());
        }
        else
        {
            // Try to equip the item instead
            return ActionResult(std::make_unique<EquipAction>(ItemSlot - 1));
        }
    }

} // namespace cm