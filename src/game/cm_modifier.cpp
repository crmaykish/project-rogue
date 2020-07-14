#include "cm_modifier.h"
#include "cm_game_world.h"
#include "cm_logger.h"

namespace cm
{
    void RandomPotionSpawnModifier::Modify(GameWorld &world)
    {
        Log("potion spawn", LOG_INFO);

        // spawn a potion in the player's inventory

        auto inv = world.GetPlayer()->GetInventory();

        if (inv->FreeSlots() > 0)
        {
            inv->AddItem(RandomConsumable());
        }
    }

} // namespace cm