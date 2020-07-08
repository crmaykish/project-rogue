#include "cm_attackaction.h"
#include "cm_logger.h"

namespace cm
{
    AttackAction::AttackAction(Actor &target)
        : Target(target) {}

    ActionResult AttackAction::Execute(Actor &executor)
    {
        if (executor.Friendly == Target.Friendly)
        {
            // actors cannot attack members of their own faction
            return ActionResult(ActionStatus::Invalid);
        }

        Target.HP -= executor.GetAttack();

        if (Target.HP <= 0)
        {
            Target.HP = 0;
            Target.Active = false;
        }

        // Attack succeeds
        auto result = ActionResult(ActionStatus::Succeeded);

        auto verb = Target.HP > 0 ? " attacked " : " killed ";
        result.Message = executor.Name + verb + Target.Name;

        return result;
    }

} // namespace cm