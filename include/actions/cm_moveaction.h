#ifndef CM_MOVEACTION_H
#define CM_MOVEACTION_H

#include "cm_action.h"
#include "cm_actor.h"
#include "cm_game_world.h"

namespace cm
{
    enum struct MoveDirection
    {
        Unknown,
        Left,
        Right,
        Up,
        Down
    };

    class MoveAction : public Action
    {
    private:
        MoveDirection Direction;
        Actor &Target;
        GameWorld &World;

    public:
        MoveAction(MoveDirection direction, Actor &target, GameWorld &world);
        ActionResult Execute() override;
    };

} // namespace cm

#endif // CM_MOVEACTION_H
