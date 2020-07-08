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
        auto newItem = std::move(Items.at(slot));

        // remove empty pointer from Items
        Items.erase(Items.begin() + slot);

        auto itemType = newItem->Type;

        auto existingItem = Equipment.find(itemType);

        if (existingItem != Equipment.end())
        {
            // there is an item already in the slot, move it back to inventory
            Items.emplace_back(std::move(existingItem->second));

            // erase now null pointer from equipment
            Equipment.erase(itemType);
        }

        // equip new item
        Equipment.emplace(itemType, std::move(newItem));
    }

    Item *Inventory::EquipmentAt(ItemType type)
    {
        if (Equipment.find(type) == Equipment.end())
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