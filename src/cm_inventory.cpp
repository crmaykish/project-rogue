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

    void Inventory::EquipItem(int slot)
    {
        // TODO: unequip any existing item first
        
        auto item = std::move(Items.at(slot));

        Equipment.emplace(item->Type, std::move(item));

        // remove empty pointer from Items
        Items.erase(Items.begin() + slot);
    }

    Item *Inventory::EquipmentAt(ItemType type)
    {
        if (Equipment.find(type)->second == nullptr)
        {
            return nullptr;
        }
        // TODO: this is kind of redundant
        return Equipment.find(type)->second.get();
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