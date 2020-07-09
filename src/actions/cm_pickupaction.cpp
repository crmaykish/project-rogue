#include "cm_pickupaction.h"
#include "cm_exitlevelaction.h"

namespace cm
{
    PickupAction::PickupAction(GameWorld &world) : World(world) {}

    ActionResult PickupAction::Execute(Actor &executor)
    {
        auto tile = World.GetTile(executor.TileX, executor.TileY);

        if (tile->Type == TileType::Door)
        {
            return ActionResult(std::make_unique<ExitLevelAction>(World));
        }

        // Does the tile contain an item to pickup?
        if (tile->Items.size() == 0)
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " has nothing to pickup");
        }

        auto message = executor.Name + " picked up ";

        for (auto &item : tile->Items)
        {
            message += item->Name + " | ";

            // Activate on-pickup effects
            item->Pickup(executor);

            // If the item has charges, add to inventory, otherwise remove it from the tile
            if (item->Charges > 0 || item->Type != ItemType::Consumable)
            {
                executor.GetInventory()->AddItem(std::move(item));
            }
        }

        tile->Items.clear();

        return ActionResult(ActionStatus::Succeeded, message);
    }

} // namespace cm