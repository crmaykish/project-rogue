#include "cm_abilityaction.h"
#include "cm_actor.h"

namespace cm
{
    AbilityAction::AbilityAction(int abilitySlot, GameWorld &world) : World(world), AbilitySlot(abilitySlot) {}

    ActionResult AbilityAction::Execute(Actor &executor)
    {
        auto abilitySet = executor.GetAbilitySet();
        auto ability = abilitySet->AbilityAt(AbilitySlot);
        auto result = ability->Use(executor, World);

        if (result)
        {
            return ActionResult(ActionStatus::Succeeded, executor.Name + " used " + ability->GetName());
        }
        else
        {
            return ActionResult(ActionStatus::Invalid, "Failed to use ability in slot: " + std::to_string(AbilitySlot));
        }
    }

} // namespace cm