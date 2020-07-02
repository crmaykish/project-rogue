#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <string>
#include <vector>
#include "cm_effect.h"

namespace cm
{
    class Item
    {
    private:
        std::vector<std::unique_ptr<Effect>> PickupEffects;
        std::vector<std::unique_ptr<Effect>> UseEffects;

    public:
        std::string Name;
        bool PickedUp = false;
        int Charges = 0;

        void Pickup(Actor &owner);
        void Use(Actor &owner);

        void AddPickupEffect(std::unique_ptr<Effect> effect);
        void AddUseEffect(std::unique_ptr<Effect> effect);
    };

    std::unique_ptr<Item> HealthPotion(int healing, int stackSize = 1);
    std::unique_ptr<Item> Torch(int fuel = 10);

} // namespace cm

#endif // CM_ITEM_H
