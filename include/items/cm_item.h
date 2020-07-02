#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <string>
#include <vector>
#include "cm_effect.h"
#include "cm_assets.h"

namespace cm
{
    enum struct ItemType
    {
        Consumable,
        Head,
        Chest,
        Legs,
        Gloves,
        Boots,
        OneHand,
        TwoHand,
        OffHand,
        Charm
    };

    class Item
    {
    private:
        std::vector<std::unique_ptr<Effect>> PickupEffects;
        std::vector<std::unique_ptr<Effect>> UseEffects;

    public:
        std::string Name;
        bool PickedUp = false;
        int Charges = 0;
        ItemType Type = ItemType::Consumable;

        AssetKey TextureKey;

        void Pickup(Actor &owner);
        void Use(Actor &owner);

        void AddPickupEffect(std::unique_ptr<Effect> effect);
        void AddUseEffect(std::unique_ptr<Effect> effect);

        AssetKey GetTextureKey();
    };

    std::unique_ptr<Item> HealthPotion(int healing, int stackSize = 1);
    std::unique_ptr<Item> Torch();

    std::unique_ptr<Item> RustyDagger();

} // namespace cm

#endif // CM_ITEM_H
