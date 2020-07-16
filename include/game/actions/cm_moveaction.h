#ifndef CM_MOVEACTION_H
#define CM_MOVEACTION_H

#include "cm_action.h"
#include "cm_game_world.h"

namespace cm
{
    static const int MoveActionBaseEnergy = 1;

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
        GameWorld &World;

    public:
        MoveAction(MoveDirection direction, GameWorld &world);
        ActionResult Execute(Actor &executor) override;
        int EnergyCost() override;
    };

} // namespace cm

#endif // CM_MOVEACTION_H
