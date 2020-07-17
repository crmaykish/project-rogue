#ifndef CM_ITEM_BUILDER_H
#define CM_ITEM_BUILDER_H

#include "cm_item.h"

namespace cm
{
    std::unique_ptr<Item> BuildItem();
    std::unique_ptr<Item> BuildItem(ItemType type);

} // namespace cm

#endif /* CM_ITEM_BUILDER_H */
