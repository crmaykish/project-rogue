#ifndef CM_POTION_H
#define CM_POTION_H

#include <memory>
#include "cm_item.h"

namespace cm
{
    class HealthPotion : public Item
    {
    public:
        HealthPotion();
        std::string GetName() override;
    };

} // namespace cm

#endif // CM_POTION_H
