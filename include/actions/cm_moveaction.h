#ifndef CM_MOVEACTION_H
#define CM_MOVEACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    enum struct MoveDirection
    {
        Unknown,
        UpLeft,
        Up,
        UpRight,
        Right,
        DownRight,
        Down,
        DownLeft,
        Left
    };

    class MoveAction : public Action
    {
    private:
        MoveDirection Direction;
        const GameWorld &World;

    public:
        MoveAction(MoveDirection direction, const GameWorld &world);
        ActionResult Execute(Actor &executor) override;
    };

} // namespace cm

#endif // CM_MOVEACTION_H
