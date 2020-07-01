#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    void Actor::AddItem(std::unique_ptr<Item> item)
    {
        Items.emplace_back(std::move(item));
    }

    void Actor::RemoveItem(int slot)
    {
        Items.erase(Items.begin() + slot);
    }

} // namespace cm
