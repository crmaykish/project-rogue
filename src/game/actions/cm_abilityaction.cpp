#include "cm_abilityaction.h"
#include "cm_actor.h"

namespace cm
{
    AbilityAction::AbilityAction(int abilitySlot, GameWorld &world) : World(world), AbilitySlot(abilitySlot) {}

    ActionResult AbilityAction::Execute(Actor &executor)
    {
        auto abilitySet = executor.GetAbilitySet();
        auto ability = abilitySet->AbilityAt(AbilitySlot);

        if (ability == nullptr)
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " has no skill in slot " + std::to_string(AbilitySlot + 1));
        }

        if (!ability->IsSelfCast())
        {
            if (executor.TargetX == 0 && executor.TargetY == 0)
            {
                return ActionResult(ActionStatus::Waiting, "Pick a target");
            }
        }

        auto result = ability->Use(executor, World);

        if (result)
        {
            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + ability->GetName());
        }
        else
        {
            return ActionResult(ActionStatus::Invalid, executor.Name + " failed to use " + ability->GetName());
        }
    }

} // namespace cm