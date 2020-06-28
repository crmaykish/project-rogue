#include "cm_item.h"

namespace cm
{
    void Item::OnPickup(std::shared_ptr<Actor> owner)
    {
        if (PickedUp)
        {
            return;
        }

        for (auto &e : PickupEffects)
        {
            e->Use(*owner);
        }
    }

    void Item::OnUse(std::shared_ptr<Actor> owner)
    {
        if (Charges == 0)
        {
            return;
        }

        for (auto &e : UseEffects)
        {
            e->Use(*owner);
        }
    }

    void Item::AddPickupEffect(std::shared_ptr<Effect> effect)
    {
        PickupEffects.emplace_back(effect);
    }

    void Item::AddUseEffect(std::shared_ptr<Effect> effect)
    {
        UseEffects.emplace_back(effect);
    }

    int Item::ChargesLeft()
    {
        return Charges;
    }

} // namespace cm