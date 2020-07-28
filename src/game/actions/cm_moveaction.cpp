#include "cm_moveaction.h"
#include "cm_abilityaction.h"
#include "cm_logger.h"

namespace cm
{
    MoveAction::MoveAction(MoveDirection direction, GameWorld &world)
        : Direction(direction), World(world) {}

    MoveAction::MoveAction(Point destination, GameWorld &world) : Destination(destination), World(world)
    {
    }

    ActionResult MoveAction::Execute(Actor &executor)
    {
        if (Destination.X == 0 && Destination.Y == 0)
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
            // Set the actor's target
            executor.Target.X = executor.Position.X + moveX;
            executor.Target.Y = executor.Position.Y + moveY;
        }
        else
        {
            executor.Target = Destination;
        }

        auto targetTile = World.GetLevel()->GetTile(executor.Target);

        // Is there a tile in the move direction?
        if (targetTile == nullptr)
        {
            return ActionResult(ActionStatus::Invalid);
        }

        // Is there another actor on the tile?
        auto actor = World.GetActor(targetTile->Position);

        if (actor != nullptr)
        {
            if (actor->Friendly != executor.Friendly)
            {
                // Attack tile only if the target is not friendly
                auto attackAbilityAction = std::make_unique<AbilityAction>(executor, 0, World);
                return ActionResult(std::move(attackAbilityAction));
            }

            return ActionResult(ActionStatus::Invalid);
        }

        // Is the tile walkable?
        if (targetTile->Walkable)
        {
            executor.Position = executor.Target;

            return ActionResult(ActionStatus::Succeeded);
        }

        return ActionResult(ActionStatus::Invalid);
    }

    int MoveAction::EnergyCost()
    {
        return MoveActionBaseEnergy;
    }

} // namespace cm