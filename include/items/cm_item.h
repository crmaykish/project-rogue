#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <string>
#include <vector>
#include "cm_effect.h"
#include "cm_assets.h"
#include "cm_stats.h"

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

    // TODO:
    // Passive
    // Chance on Hit
    // Chance on Defend

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

        int BaseDamage = 0;
        int BaseArmor = 0;
        int BaseResist = 0;

        void Pickup(Actor &owner);
        void Use(Actor &owner);

        void AddPickupEffect(std::unique_ptr<Effect> effect);
        void AddUseEffect(std::unique_ptr<Effect> effect);

        AssetKey GetTextureKey();
    };

    // Item Creation
    std::unique_ptr<Item> HealthPotion(int healing, int stackSize = 1);
    std::unique_ptr<Item> Torch();
    std::unique_ptr<Item> RustyDagger();
    std::unique_ptr<Item> Sword();
    std::unique_ptr<Item> LeatherHelmet();
    std::unique_ptr<Item> LeatherBoots();
    std::unique_ptr<Item> Buckler();
    std::unique_ptr<Item> Shield();
    std::unique_ptr<Item> Bow();
    std::unique_ptr<Item> Crossbow();
    std::unique_ptr<Item> SpellBook();

    std::unique_ptr<Item> RandomItem();

} // namespace cm

#endif // CM_ITEM_H
