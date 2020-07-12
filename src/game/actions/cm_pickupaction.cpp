#include "cm_pickupaction.h"
#include "cm_exitlevelaction.h"

namespace cm
{
    PickupAction::PickupAction(GameWorld &world) : World(world) {}

    ActionResult PickupAction::Execute(Actor &executor)
    {
        auto tile = World.GetLevel()->GetTile(executor.TileX, executor.TileY);

        if (tile->Type == TileType::Door)
        {
            return ActionResult(std::make_unique<ExitLevelAction>(World));
        }

        // Does the tile contain an item to pickup?
        if (tile->Items.size() == 0)
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " has nothing to pickup");
        }

        std::string pickupMessage;

        int itemsPickedUp = 0;

        for (auto &item : tile->Items)
        {
            if (executor.GetInventory()->FreeSlots() > 0)
            {
                World.LogEvent(executor.Name + " picked up " + item->DisplayName(), executor.Friendly);

                // Activate on-pickup effects
                item->Pickup(executor);

                // If the item has charges, add to inventory, otherwise remove it from the tile
                if (item->Charges > 0 || item->Type != ItemType::Consumable)
                {
                    executor.GetInventory()->AddItem(std::move(item));
                }

                itemsPickedUp++;
            }
            else
            {
                World.LogEvent(executor.Name + " cannot carry " + item->DisplayName(), executor.Friendly);
            }
        }

        // Remove picked-up items from the tile
        if (itemsPickedUp > 0)
        {
            tile->Items.erase(tile->Items.begin(), tile->Items.begin() + itemsPickedUp);
        }

        return ActionResult(ActionStatus::Succeeded);
    }

} // namespace cm