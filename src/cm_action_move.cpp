#include "cm_action_move.h"

namespace cm
{
    MoveAction::MoveAction(Actor &actor, World &world)
        : TargetActor(actor), TargetWorld(world) {}

    void MoveAction::Execute()
    {
    }

} // namespace cm