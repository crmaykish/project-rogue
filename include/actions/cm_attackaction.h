#ifndef CM_ATTACKACTION_H
#define CM_ATTACKACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    class AttackAction : public Action
    {
    private:
        Actor &Target;
        const GameWorld &World;

    public:
        AttackAction(Actor &target, const GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_ATTACKACTION_H
