#ifndef CM_INVENTORY_H
#define CM_INVENTORY_H

#include <memory>
#include "cm_item.h"

namespace cm
{
    const int DefaultItemCountMax = 10;

    class Inventory
    {
    private:
        int ItemCountMax = DefaultItemCountMax;
        std::vector<std::unique_ptr<Item>> Items;

    public:
        void AddItem(std::unique_ptr<Item> item);
        void RemoveItem(int slot);
        Item *ItemAt(int slot);

        int ItemCount();
        int InventorySize();

        // const std::vector<std::unique_ptr<Item>> &GetItems();
    };
} // namespace cm

#endif // CM_INVENTORY_H
