#ifndef CM_ATTACKACTION_H
#define CM_ATTACKACTION_H

#include "cm_action.h"
#include "cm_actor.h"
#include "cm_game_world.h"

namespace cm
{
    class AttackAction : public Action
    {
    private:
        Actor &AttackTarget;
        Actor &Target;  // this is a bad name in this context
        GameWorld &World;
    public:
        AttackAction(Actor &attackTarget, Actor &target, GameWorld &world);
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_ATTACKACTION_H
