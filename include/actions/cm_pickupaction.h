#ifndef CM_PICKUPACTION_H
#define CM_PICKUPACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    class PickupAction : public Action
    {
    private:
        const GameWorld &World;

    public:
        PickupAction(const GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_PICKUPACTION_H
