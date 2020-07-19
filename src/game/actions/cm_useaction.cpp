#include "cm_useaction.h"
#include "cm_equipaction.h"
#include "cm_actor.h"

namespace cm
{
    UseAction::UseAction(int itemSlot, GameWorld &world)
        : ItemSlot(itemSlot), World(world) {}

    ActionResult UseAction::Execute(Actor &executor)
    {
        auto item = executor.InventoryComp->ItemAt(ItemSlot - 1);

        if (item == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, "No item in slot: " + std::to_string(ItemSlot));
        }

        auto itemName = item->DisplayName();

        if (item->Type == ItemType::Consumable)
        {
            // Use the item
            // item->Use(ItemModifierTrigger::Use, executor, World);

            if (item->Charges == 0)
            {
                executor.InventoryComp->RemoveItem(ItemSlot - 1);
            }

            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + itemName);
        }
        else
        {
            // Try to equip the item instead
            return ActionResult(std::make_unique<EquipAction>(ItemSlot - 1));
        }
    }

} // namespace cm