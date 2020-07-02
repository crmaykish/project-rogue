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

        // Move the item from the tile to the actor's inventory
        executor.GetInventory()->AddItem(std::move(tile->Items));

        return ActionResult(ActionStatus::Succeeded, message);
    }

} // namespace cm