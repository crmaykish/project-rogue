#ifndef CM_COMPONENT_H
#define CM_COMPONENT_H

#include <memory>
#include "cm_actor.h"

namespace cm
{
    class Component
    {
    public:
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
    };

} // namespace cm

#endif // CM_COMPONENT_H
