#include "cm_moveaction.h"
#include "cm_attackaction.h"
#include "cm_logger.h"

namespace cm
{
    MoveAction::MoveAction(MoveDirection direction, const GameWorld &world)
        : Direction(direction), World(world) {}

    ActionResult MoveAction::Execute(Actor &executor)
    {
        int moveX = 0;
        int moveY = 0;

        switch (Direction)
        {
        // TODO: add diagonal movement
        case MoveDirection::Left:
            moveX = -1;
            break;
        case MoveDirection::Right:
            moveX = 1;
            break;
        case MoveDirection::Up:
            moveY = 1;
            break;
        case MoveDirection::Down:
            moveY = -1;
            break;
        default:
            break;
        }

        auto targetTile = World.GetTile(executor.TileX + moveX, executor.TileY + moveY);

        // Is there a tile in the move direction?
        if (targetTile == nullptr)
        {
            return ActionResult(ActionStatus::Invalid);
        }

        // Is there an enemy on the tile?
        // auto enemy = World.GetActor(targetTile->X, targetTile->Y);

        // if (enemy != nullptr)
        // {
        //     return ActionResult(std::make_unique<AttackAction>(*enemy));
        // }

        // Is the tile empty?
        if (targetTile->Type == TileType::Empty)
        {
            executor.TileX += moveX;
            executor.TileY += moveY;

            return ActionResult(ActionStatus::Succeeded);
        }

        return ActionResult(ActionStatus::Invalid);
    }

} // namespace cm