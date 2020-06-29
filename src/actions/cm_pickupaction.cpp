#include "cm_pickupaction.h"

namespace cm
{
    PickupAction::PickupAction(Actor &target, std::shared_ptr<Tile> targetTile)
        : Target(target), TargetTile(targetTile) {}

    ActionResult PickupAction::Execute()
    {
        ActionResult result;

        if (TargetTile->Item != nullptr)
        {
            // move the item from the tile to the actor's inventory

            // TODO: items should be unique pointers and use move since there's no need to share them
            result.Message = Target.GetName() + " picked up " + TargetTile->Item->GetName();
            
            Target.AddItem(TargetTile->Item);
            TargetTile->Item = nullptr;

            result.Success = true;
        }

        return result;
    }

} // namespace cm