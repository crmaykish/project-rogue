#include "cm_item.h"

namespace cm
{
    void Item::Pickup(Actor &owner)
    {
        if (PickedUp)
        {
            return;
        }

        for (auto &e : PickupEffects)
        {
            e->Use(owner);
        }

        PickedUp = true;
    }

    void Item::Use(Actor &owner)
    {
        if (Charges == 0)
        {
            return;
        }

        for (auto &e : UseEffects)
        {
            e->Use(owner);
        }

        Charges--;
    }

    void Item::AddPickupEffect(std::shared_ptr<Effect> effect)
    {
        PickupEffects.emplace_back(effect);
    }

    void Item::AddUseEffect(std::shared_ptr<Effect> effect)
    {
        UseEffects.emplace_back(effect);
    }

    // Item Definitions

    std::unique_ptr<Item> HealthPotion(int healing, int stackSize)
    {
        auto hp = std::make_unique<Item>();

        hp->Name = "Health Potion";
        hp->Charges = stackSize;
        hp->AddUseEffect(std::make_shared<HealEffect>());

        // TODO: is it bad to return move?
        return std::move(hp);
    }

} // namespace cm