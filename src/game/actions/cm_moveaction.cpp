#include "cm_moveaction.h"
#include "cm_abilityaction.h"
#include "cm_logger.h"

namespace cm
{
    MoveAction::MoveAction(MoveDirection direction, GameWorld &world)
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

        auto targetTile = World.GetLevel()->GetTile(executor.TileX + moveX, executor.TileY + moveY);

        // Is there a tile in the move direction?
        if (targetTile == nullptr)
        {
            return ActionResult(ActionStatus::Invalid);
        }

        // Is there another actor on the tile?
        auto actor = World.GetActor(targetTile->X, targetTile->Y);

        if (actor != nullptr)
        {
            if (actor->Friendly != executor.Friendly)
            {
                // Attack tile only if the target is not friendly
                auto attackAbilityAction = std::make_unique<AbilityAction>(0, World);
                attackAbilityAction->SetTarget(targetTile->X, targetTile->Y);
                return ActionResult(std::move(attackAbilityAction));
            }

            return ActionResult(ActionStatus::Invalid);
        }

        // Is the tile walkable?
        if (targetTile->Type != TileType::Wall)
        {
            executor.TileX += moveX;
            executor.TileY += moveY;

            return ActionResult(ActionStatus::Succeeded);
        }

        return ActionResult(ActionStatus::Invalid);
    }

} // namespace cm