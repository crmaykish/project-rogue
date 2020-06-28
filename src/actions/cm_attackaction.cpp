#include "cm_attackaction.h"
#include "cm_logger.h"

namespace cm
{
    AttackAction::AttackAction(Actor &attackTarget, Actor &target, GameWorld &world)
        : AttackTarget(attackTarget), Target(target), World(world) {}

    ActionResult AttackAction::Execute()
    {
        ActionResult result;

        if (AttackTarget.GetFaction() != Target.GetFaction())
        {
            int attackDamage = Target.GetAttack();
            AttackTarget.Damage(attackDamage);

            if (AttackTarget.GetHP() > 0)
            {
                result.Message = Target.GetName() + " attacks " + AttackTarget.GetName();
            }
            else
            {
                result.Message = Target.GetName() + " killed " + AttackTarget.GetName();
            }

            result.Success = true;
        }

        return result;
    }

} // namespace cm