#include "cm_pickupaction.h"

namespace cm
{
    PickupAction::PickupAction(const GameWorld &world) : World(world) {}

    ActionResult PickupAction::Execute(Actor &executor)
    {
        auto tile = World.GetTile(executor.TileX, executor.TileY);

        // Does the tile contain an item to pickup?
        if (tile->Items.get() == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " has nothing to pickup");
        }

        auto message = executor.Name + " picked up " + tile->Items->Name;

        // Activate on-pickup effects
        tile->Items->Pickup(executor);

        // If the item has charges, add to inventory, otherwise remove it from the tile
        if (tile->Items->Charges > 0 || tile->Items->Type != ItemType::Consumable)
        {
            executor.GetInventory()->AddItem(std::move(tile->Items));
        }
        else
        {
            tile->Items.reset();
        }

        return ActionResult(ActionStatus::Succeeded, message);
    }

} // namespace cm