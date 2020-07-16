#include "cm_abilityaction.h"
#include "cm_actor.h"

namespace cm
{
    AbilityAction::AbilityAction(Actor &actor, int abilitySlot, GameWorld &world) : World(world), AbilitySlot(abilitySlot)
    {
        auto abilitySet = actor.GetAbilitySet();
        ExecutorAbility = abilitySet->AbilityAt(abilitySlot);
    }

    ActionResult AbilityAction::Execute(Actor &executor)
    {
        if (ExecutorAbility == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " has no skill in slot " + std::to_string(AbilitySlot + 1));
        }

        if (!ExecutorAbility->IsSelfCast())
        {
            if (executor.Target.X == 0 && executor.Target.Y == 0)
            {
                return ActionResult(ActionStatus::Waiting, "Pick a target");
            }
        }

        auto result = ExecutorAbility->Use(executor, World);

        if (result)
        {
            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + ExecutorAbility->GetName());
        }
        else
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " failed to use " + ExecutorAbility->GetName());
        }
    }

    int AbilityAction::EnergyCost()
    {
        if (ExecutorAbility == nullptr)
        {
            return 0;
        }
        else
        {
            return ExecutorAbility->EnergyCost();
        }
    }

} // namespace cm