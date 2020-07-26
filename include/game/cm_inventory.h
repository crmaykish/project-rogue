#ifndef CM_INVENTORY_H
#define CM_INVENTORY_H

#include <memory>
#include <map>
#include "cm_item.h"
#include "cm_actor_stat.h"

namespace cm
{
    const int BeltSize = 9;

    class Inventory
    {
    private:
        /**
         * @brief A reference to the Inventory owner's stat set
         */
        ActorStatSet &OwnerStats;
        EffectComponent &OwnerEffects;

        std::array<std::unique_ptr<Item>, BeltSize> Items;
        std::map<ItemType, std::unique_ptr<Item>> Equipment;

        int FirstOpenSlot();

    public:
        Inventory(ActorStatSet &ownerStats, EffectComponent &ownerEffects);

        void AddItem(std::unique_ptr<Item> item);
        void RemoveItem(int slot);
        Item *ItemAt(int slot);

        int InventorySize();
        int FreeSlots();

        void EquipItem(int slot);
        void UnequipItem(ItemType type);
        Item *EquipmentAt(ItemType type);

        std::map<ItemType, std::unique_ptr<Item>> &GetEquipment()
        {
            return Equipment;
        }

        void Reset();
    };
} // namespace cm

#endif // CM_INVENTORY_H
