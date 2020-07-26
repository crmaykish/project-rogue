#ifndef CM_BOSS_MAP_H
#define CM_BOSS_MAP_H

#include "cm_room_accretion_map.h"

namespace cm
{
    class BossMap : public RoomAccretionMap
    {
    public:
        void Generate() override;
        std::vector<std::unique_ptr<Actor>> SpawnNPCs(int playerLevel) override;
    };

} // namespace cm

#endif /* CM_BOSS_MAP_H */
