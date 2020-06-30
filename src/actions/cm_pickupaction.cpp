#include "cm_pickupaction.h"

namespace cm
{
    PickupAction::PickupAction(GameWorld &world) : World(world) {}

    ActionResult PickupAction::Execute(Actor &executor)
    {
        auto tile = World.GetTile(executor.GetX(), executor.GetY());

        // Does the tile contain an item to pickup?
        if (tile->Items.get() == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, executor.GetName() + " has nothing to pickup");
        }

        auto message = executor.GetName() + " picked up " + tile->Items->GetName();

        // Move the item from the tile to the actor's inventory
        executor.AddItem(std::move(tile->Items));

        return ActionResult(ActionStatus::Succeeded, message);
    }

} // namespace cm