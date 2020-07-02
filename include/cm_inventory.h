#ifndef CM_INVENTORY_H
#define CM_INVENTORY_H

#include <memory>
#include <unordered_map>
#include "cm_item.h"

namespace cm
{
    const int DefaultItemCountMax = 10;

    class Inventory
    {
    private:
        int ItemCountMax = DefaultItemCountMax;
        std::vector<std::unique_ptr<Item>> Items;
        std::unordered_map<ItemType, std::unique_ptr<Item>> Equipment;

    public:
        void AddItem(std::unique_ptr<Item> item);
        void RemoveItem(int slot);
        Item *ItemAt(int slot);

        int ItemCount();
        int InventorySize();

        void EquipItem(int slot);
        Item *EquipmentAt(ItemType type);

    };
} // namespace cm

#endif // CM_INVENTORY_H
