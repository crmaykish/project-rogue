#ifndef CM_EXITLEVELACTION_H
#define CM_EXITLEVELACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    class ExitLevelAction : public Action
    {
    private:
        GameWorld &World;

    public:
        ExitLevelAction(GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_EXITLEVELACTION_H
