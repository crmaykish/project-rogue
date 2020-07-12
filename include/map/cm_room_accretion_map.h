#ifndef CM_ROOM_ACCRETION_MAP_H
#define CM_ROOM_ACCRETION_MAP_H

#include "cm_map.h"

namespace cm
{
    class RoomAccretionMap : public Map
    {
    private:
        void BuildRoom(int x, int y, int width, int height);

    public:
        void Generate() override;
    };
} // namespace cm

#endif /* CM_ROOM_ACCRETION_MAP_H */
