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

    struct ItemModifier
    {
        std::string Name;
        int PercentChance = 100;
        std::unique_ptr<Effect> MainEffect;
    };

    class Item
    {
    private:
        // TODO: Item stat modifiers

        // TODO: Actor stat modifiers

        /**
         * @brief Effects that trigger when an actor picks up the item
         */
        std::vector<std::unique_ptr<Effect>> PickupEffects;

        /**
         * @brief Modifiers that trigger when an actor uses the item.
         * 
         * For consumables, this means activating the item in inventory.
         * 
         * For weapons, this means attacking an enemy.
         * 
         * For armor, this means taking damage.
         */
        std::vector<ItemModifier> OnUseModifiers;

        // TODO: OnKillModifiers

    public:
        std::string Name;
        std::string Description;
        ItemType Type = ItemType::Consumable;
        AssetKey TextureKey;

        bool PickedUp = false;

        bool LimitedCharge = false;
        int Charges = 0;

        int BaseDamage = 0;
        int BaseArmor = 0;
        int BaseResist = 0;

        void Pickup(Actor &owner, GameWorld &world);
        void Use(Actor &owner, GameWorld &world);

        void AddPickupEffect(std::unique_ptr<Effect> effect);

        void AddOnUseModifier(std::string name, std::unique_ptr<Effect> effect, int percentChance = 100);

        AssetKey GetTextureKey();

        std::string DisplayName();
    };

    // Weapons
    std::unique_ptr<Item> Dagger();
    std::unique_ptr<Item> ShortSword();
    std::unique_ptr<Item> LongSword();

    // Armor

    // Consumables
    std::unique_ptr<Item> HealingPotion();
    std::unique_ptr<Item> ManaPotion();

    // Random
    std::unique_ptr<Item> RandomConsumable();
    std::unique_ptr<Item> RandomItem();

} // namespace cm

#endif // CM_ITEM_H
