#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <vector>
#include "cm_effect.h"

namespace cm
{
    class Item
    {
    protected:
        int Charges = 0;
        int PickedUp = false;
        std::vector<std::shared_ptr<Effect>> PickupEffects;
        std::vector<std::shared_ptr<Effect>> UseEffects;

    public:
        void OnPickup(Actor &owner);
        void OnUse(Actor &owner);

        void AddPickupEffect(std::shared_ptr<Effect> effect);
        void AddUseEffect(std::shared_ptr<Effect> effect);

        int ChargesLeft();

        virtual std::string GetName() = 0;
    };

} // namespace cm

#endif // CM_ITEM_H
