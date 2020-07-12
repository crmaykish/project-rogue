#ifndef CM_CELLULAR_AUTOMATA_MAP_H
#define CM_CELLULAR_AUTOMATA_MAP_H

#include "cm_map.h"

namespace cm
{
    class CellularAutomataMap : public Map
    {
    public:
        void Generate() override;
    };

} // namespace cm

#endif /* CM_CELLULAR_AUTOMATA_MAP_H */
