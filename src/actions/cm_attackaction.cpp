#include "cm_attackaction.h"
#include "cm_logger.h"

namespace cm
{
    AttackAction::AttackAction(Actor &target, GameWorld &world)
        : Target(target), World(world) {}

    ActionResult AttackAction::Execute(Actor &executor)
    {
        if (Target.GetFaction() != Target.GetFaction())
        {
            // actors cannot attack members of their own faction
            return ActionResult(ActionStatus::Invalid);
        }

        Target.Damage(executor.GetAttack());

        // Attack succeeds
        auto result = ActionResult(ActionStatus::Succeeded);

        auto verb = Target.GetHP() > 0 ? " attacked " : " killed ";
        result.Message = executor.GetName() + verb + Target.GetName();

        return result;
    }

} // namespace cm