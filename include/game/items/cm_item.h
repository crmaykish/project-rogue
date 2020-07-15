#ifndef CM_ITEM_H
#define CM_ITEM_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "cm_assets.h"
#include "cm_item_modifier.h"
#include "cm_actor_stat.h"

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
        // TODO: Item stat modifiers, e.g. extra base damage/armor

        /**
         * @brief Modifiers that directly change the owning actor's stats when the item is equipped
         */
        std::vector<ActorStatModifier> StatModifiers;

        /**
         * @brief Modifiers that trigger when an item is used. The usage condition
         * depends on the trigger type.
         */
        std::unordered_map<ItemModifierTrigger, std::vector<ItemModifier>> Modifiers; // TODO: rename to BehaviorModifiers?

    public:
        std::string Name;
        std::string Description;
        ItemType Type = ItemType::Consumable;
        AssetKey TextureKey;

        bool PickedUp = false;

        bool LimitedCharge = false;
        int Charges = 0;

        /**
         * @brief The base attack rating that an actor receives by equipping this item
         */
        int BaseAttack = 0;

        /**
         * @brief The base defense rating that an actor receives by equipping this item
         */
        int BaseDefense = 0;

        void Use(ItemModifierTrigger trigger, Actor &owner, GameWorld &world);

        void AddStatModifier(ActorStatModifier statModifier);
        std::vector<ActorStatModifier> &GetStatModifiers();
        void AddModifier(ItemModifierTrigger trigger, ItemModifier modifier);

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
    std::unique_ptr<Item> RejuvPotion();

    // Random
    std::unique_ptr<Item> RandomConsumable();
    std::unique_ptr<Item> RandomItem();

} // namespace cm

#endif // CM_ITEM_H
