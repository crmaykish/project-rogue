#include "cm_inventory.h"

namespace cm
{
    void Inventory::AddItem(std::unique_ptr<Item> item)
    {
        Items.emplace_back(std::move(item));
    }

    void Inventory::RemoveItem(int slot)
    {
        Items.erase(Items.begin() + slot);
    }

    Item *Inventory::ItemAt(int slot)
    {
        if (slot < 0 || slot >= ItemCount())
        {
            return nullptr;
        }

        return Items.at(slot).get();
    }

    int Inventory::ItemCount()
    {
        return Items.size();
    }

    int Inventory::InventorySize()
    {
        return ItemCountMax;
    }

} // namespace cm