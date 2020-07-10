#ifndef CM_ABILITYACTION_H
#define CM_ABILITYACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    class AbilityAction : public Action
    {
    private:
        GameWorld &World;
        int AbilitySlot = 0;

    public:
        AbilityAction(int abilitySlot, GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif /* CM_ABILITYACTION_H */
