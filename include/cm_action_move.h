#ifndef CM_ACTION_MOVE_H
#define CM_ACTION_MOVE_H

#include <memory>
#include "cm_action.h"
#include "cm_actor.h"
#include "cm_world.h"

namespace cm
{
    class MoveAction : public Action
    {
    private:
        Actor &TargetActor;
        World &TargetWorld;

    public:
        MoveAction(Actor &actor, World &world);
        void Execute() override;
    };
} // namespace cm

#endif // CM_ACTION_MOVE_H
