#include "cm_component.h"

namespace cm
{
    Component::Component(std::shared_ptr<Actor> owner) : Owner(owner) {}
    
} // namespace cm