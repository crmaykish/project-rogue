#ifndef CM_WAITACTION_H
#define CM_WAITACTION_H

#include "cm_action.h"
#include "cm_actor.h"
#include "cm_game_world.h"

namespace cm
{
    class WaitAction : public Action
    {
    private:
        Actor &Target;
        GameWorld &World;

    public:
        WaitAction(Actor &target, GameWorld &world);
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_WAITACTION_H
