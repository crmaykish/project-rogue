#include "cm_inventory.h"

namespace cm
{
    Inventory::Inventory(ActorStatSet &ownerStats) : OwnerStats(ownerStats) {}

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
        // Note: move this here instead of take a reference so the inventory slot frees up immediately
        auto newItem = std::move(Items.at(slot));

        // Unequip any existing item in the slot
        UnequipItem(newItem->Type);

        // Add item stat modifiers to actor
        for (auto const &mod : newItem->GetStatModifiers())
        {
            OwnerStats.AddStatModifier(mod.GetStatType(), mod);
        }

        // Equip new item
        Equipment.emplace(newItem->Type, std::move(newItem));
    }

    void Inventory::UnequipItem(ItemType type)
    {
        auto equipped = EquipmentAt(type);

        if (equipped == nullptr)
        {
            return;
        }

        if (FreeSlots() == 0)
        {
            // TODO: drop item on the ground instead
            return;
        }

        // Remove any item stat modifiers from the actor that came from this item
        for (auto &mod : equipped->GetStatModifiers())
        {
            OwnerStats.RemoveStatModifier(mod.GetId());
        }

        // Move the item back to the inventory and erase it from the equipment map
        AddItem(std::move(Equipment.at(type)));
        Equipment.erase(type);
    }

    Item *Inventory::EquipmentAt(ItemType type)
    {
        if (Equipment.find(type) == Equipment.end())
        {
            return nullptr;
        }

        return Equipment.at(type).get();
    }

    int Inventory::InventorySize()
    {
        return Items.size();
    }

    void Inventory::Reset()
    {
        // TODO: remove all item stat modifiers from actor

        for (auto &b : Items)
        {
            b.reset();
        }

        Equipment.clear();
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