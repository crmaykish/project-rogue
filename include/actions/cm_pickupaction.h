#ifndef CM_PICKUPACTION_H
#define CM_PICKUPACTION_H

#include <memory>
#include "cm_action.h"
#include "cm_actor.h"
#include "cm_tile.h"

namespace cm
{
    class PickupAction : public Action
    {
    private:
        Actor &Target;
        std::shared_ptr<Tile> TargetTile;

    public:
        PickupAction(Actor &target, std::shared_ptr<Tile> targetTile);
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_PICKUPACTION_H
