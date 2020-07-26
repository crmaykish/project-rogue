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
            auto itemEffectsMap = item->Effects.Effects;

            if (itemEffectsMap.find(EffectTrigger::UseItem) != itemEffectsMap.end())
            {
                // Use item effects
                for (auto const &effect : itemEffectsMap.at(EffectTrigger::UseItem))
                {
                    effect->Use(&executor, nullptr, &World);
                }
            }

            executor.InventoryComp->RemoveItem(ItemSlot - 1);

            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + itemName);
        }
        else if (item->Type != ItemType::Quest)
        {
            // Try to equip the item instead
            return ActionResult(std::make_unique<EquipAction>(ItemSlot - 1));
        }

        return ActionResult(ActionStatus::Invalid, "Cannot use " + itemName);
    }

} // namespace cm