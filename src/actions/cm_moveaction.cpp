#include "cm_moveaction.h"
#include "cm_attackaction.h"
#include "cm_logger.h"

namespace cm
{
    MoveAction::MoveAction(MoveDirection direction, Actor &target, GameWorld &world)
        : Direction(direction), Target(target), World(world) {}

    ActionResult MoveAction::Execute()
    {
        ActionResult result;

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
            break;
        }

        auto targetTile = World.GetTile(Target.GetX() + moveX, Target.GetY() + moveY);

        // is it an exit tile?
        // TODO: create NextLevelAction?
        if (targetTile.Type == TileType::Door && Target.GetFaction() == Faction::Human)
        {
            World.SetNextLevel();
            result.Success = true;
            result.Message = Target.GetName() + " is exiting level";
        }

        auto enemyOnTargetTile = World.GetActor(targetTile.X, targetTile.Y);

        // Is there an enemy on the tile?
        if (enemyOnTargetTile != nullptr)
        {
            result.AlternateAction = std::make_shared<AttackAction>(*enemyOnTargetTile, Target, World);
        }
        else if (targetTile.Type == TileType::Empty)
        {
            Target.Move(moveX, moveY);
            result.Success = true;
            result.Message = Target.GetName() + " moves " + dirName;
        }

        return result;
    }

} // namespace cm