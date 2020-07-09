#include "cm_attackaction.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    AttackAction::AttackAction(Actor &target, const GameWorld &world)
        : Target(target), World(world) {}

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

            if (!Target.Friendly)
            {
                Target.Active = false;

                // Drop loot
                if (RandomInt(100) < 20)
                {
                    World.GetTile(Target.TileX, Target.TileY)->Items.emplace_back(RandomItem());
                }

                // Award experience
                executor.Experience += (100 * Target.Level);

                // TODO: this should not be in the attack action class
                if (executor.Experience >= (executor.Level * 1000))
                {
                    // Scale health pool
                    executor.MaxHP *= 1.5;
                    executor.HP = executor.MaxHP;

                    // Reset experience counter
                    executor.Experience -= (executor.Level * 1000);

                    // Level up
                    executor.Level++;
                }
            }
        }

        // Attack succeeds
        auto result = ActionResult(ActionStatus::Succeeded);

        auto verb = Target.HP > 0 ? " attacked " : " killed ";
        result.Message = executor.Name + verb + Target.Name;

        return result;
    }

} // namespace cm