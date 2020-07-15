#include "cm_inventory.h"

namespace cm
{
    void Inventory::AddItem(std::unique_ptr<Item> item)
    {
        int firstOpenSlot = FirstOpenSlot();

        if (firstOpenSlot != -1)
        {
            Items[firstOpenSlot] = std::move(item);
        }
    }

    void Inventory::RemoveItem(int slot)
    {
        Items.at(slot).reset();
    }

    Item *Inventory::ItemAt(int slot)
    {
        if (slot < 0 || slot >= InventorySize())
        {
            return nullptr;
        }

        return Items.at(slot).get();
    }

    void Inventory::EquipItem(int slot)
    {
        auto newItem = std::move(Items.at(slot));

        auto itemType = newItem->Type;

        auto existingItem = Equipment.find(itemType);

        if (existingItem != Equipment.end())
        {
            // there is an item already in the slot, move it back to inventory
            AddItem(std::move(existingItem->second));

            // erase now null pointer from equipment
            Equipment.erase(itemType);
        }

        // equip new item
        Equipment.emplace(itemType, std::move(newItem));

        RecalculateTotalStats();
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

    int Inventory::InventorySize()
    {
        return Items.size();
    }

    int Inventory::GetAddedAttack()
    {
        return AddedAttack;
    }

    int Inventory::GetAddedDefense()
    {
        return AddedDefense;
    }

    void Inventory::RecalculateTotalStats()
    {
        // recalculate added attack and defense
        AddedAttack = 0;
        AddedDefense = 0;

        for (auto &e : Equipment)
        {
            AddedAttack += e.second->BaseAttack;
            AddedDefense += e.second->BaseDefense;
        }
    }

    void Inventory::Reset()
    {
        for (auto &b : Items)
        {
            b.reset();
        }

        Equipment.clear();

        RecalculateTotalStats();
    }

    int Inventory::FreeSlots()
    {
        int freeSlots = 0;

        for (int i = 0; i < InventorySize(); i++)
        {
            if (ItemAt(i) == nullptr)
            {
                freeSlots++;
            }
        }

        return freeSlots;
    }

    int Inventory::FirstOpenSlot()
    {
        for (int i = 0; i < InventorySize(); i++)
        {
            if (ItemAt(i) == nullptr)
            {
                return i;
            }
        }

        return -1;
    }

} // namespace cm