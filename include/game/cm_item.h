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

        int BaseDamage = 0;
        int BaseArmor = 0;
        int BaseResist = 0;

        void Pickup(Actor &owner, GameWorld &world);
        void Use(Actor &owner, GameWorld &world);

        void AddPickupEffect(std::unique_ptr<Effect> effect);
        void AddUseEffect(std::unique_ptr<Effect> effect);

        AssetKey GetTextureKey();

        std::string DisplayName();
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
    std::unique_ptr<Item> Axe();
    std::unique_ptr<Item> BattleAxe();
    std::unique_ptr<Item> Beer();
    std::unique_ptr<Item> Wine();
    std::unique_ptr<Item> Club();
    std::unique_ptr<Item> Falchion();
    std::unique_ptr<Item> Hammer();
    std::unique_ptr<Item> TowerShield();
    std::unique_ptr<Item> Staff();
    std::unique_ptr<Item> Wand();
    // std::unique_ptr<Item> Bone();
    // std::unique_ptr<Item> Bottle();

    std::unique_ptr<Item> Charm();

    std::unique_ptr<Item> RandomConsumable();
    std::unique_ptr<Item> RandomWeapon();
    std::unique_ptr<Item> RandomArmor();
    std::unique_ptr<Item> RandomItem();

} // namespace cm

#endif // CM_ITEM_H
