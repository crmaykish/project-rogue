#include "cm_moveaction.h"
#include "cm_logger.h"

namespace cm
{
    MoveAction::MoveAction(MoveDirection direction, Actor &target, GameWorld &world)
        : Direction(direction), Target(target), World(world) {}

    ActionResult MoveAction::Execute()
    {
        auto result = ActionResult{false, nullptr};

        // try to move the actor in the given direction
        int moveX = 0;
        int moveY = 0;

        std::string dirName;

        switch (Direction)
        {
        case MoveDirection::Left:
            moveX = -1;
            dirName = "left";
            break;
        case MoveDirection::Right:
            moveX = 1;
            dirName = "right";
            break;
        case MoveDirection::Up:
            moveY = 1;
            dirName = "up";
            break;
        case MoveDirection::Down:
            moveY = -1;
            dirName = "down";
            break;
        default:
            Log("Tried to move in invalid direction", LOG_WARNING);
            break;
        }

        auto targetTile = World.GetTile(Target.GetX() + moveX, Target.GetY() + moveY);

        auto enemyOnTargetTile = World.GetActor(targetTile.X, targetTile.Y);

        // If target tile is walkable and does not contain another actor, move to that tile
        if (targetTile.Type == TileType::Empty && enemyOnTargetTile == nullptr)
        {
            Target.Move(moveX, moveY);
            result.Success = true;
        }

        if (result.Success)
        {
            Log(Target.GetName() + " moved " + dirName, LOG_INFO);
        }
        else
        {
            Log(Target.GetName() + " failed to move " + dirName, LOG_INFO);
        }

        return result;
    }

} // namespace cm