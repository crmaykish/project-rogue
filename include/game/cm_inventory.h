#ifndef CM_INVENTORY_H
#define CM_INVENTORY_H

#include <memory>
#include <unordered_map>
#include "cm_item.h"

namespace cm
{
    const int BeltSize = 9;

    class Inventory
    {
    private:
        std::array<std::unique_ptr<Item>, BeltSize> Items;
        std::unordered_map<ItemType, std::unique_ptr<Item>> Equipment;

        int AddedAttack = 0;
        int AddedDefense = 0;

        void RecalculateTotalStats();
        int FirstOpenSlot();

    public:
        void AddItem(std::unique_ptr<Item> item);
        void RemoveItem(int slot);
        Item *ItemAt(int slot);

        int InventorySize();
        int FreeSlots();

        void EquipItem(int slot);
        Item *EquipmentAt(ItemType type);

        int GetAddedAttack();
        int GetAddedDefense();

        void Reset();
    };
} // namespace cm

#endif // CM_INVENTORY_H
