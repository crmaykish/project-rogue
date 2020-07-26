#include "cm_exitlevelaction.h"

namespace cm
{
    ExitLevelAction::ExitLevelAction(GameWorld &world) : World(world) {}

    ActionResult ExitLevelAction::Execute(Actor &executor)
    {
        auto door = World.GetLevel()->GetTile(executor.Position.X, executor.Position.Y);

        if (door->Type != TileType::Door)
        {
            return ActionResult(ActionStatus::Invalid, "There is no door here");
        }

        if (door->DoorLocked)
        {
            bool hasKey = false;
            int keySlot = -1;

            auto &inv = executor.InventoryComp;

            for (auto i = 0; i < inv->InventorySize(); i++)
            {
                if (inv->ItemAt(i) != nullptr)
                {
                    if (inv->ItemAt(i)->Type == ItemType::Quest)
                    {
                        hasKey = true;
                        keySlot = i;
                    }
                }
            }

            if (hasKey)
            {
                // Remove the key from inventory
                inv->RemoveItem(keySlot);
            }
            else
            {
                return ActionResult(ActionStatus::Invalid, "The door is locked");
            }
        }

        World.SetNextLevel();
        return ActionResult(ActionStatus::Succeeded);
    }

} // namespace cm