#ifndef CM_USEACTION_H
#define CM_USEACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    class UseAction : public Action
    {
    private:
        int ItemSlot = 0;
        GameWorld &World;

    public:
        UseAction(int itemSlot, GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_USEACTION_H
