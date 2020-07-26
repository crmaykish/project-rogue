#include "cm_boss_map.h"
#include "cm_enemy.h"
#include "cm_random.h"

namespace cm
{
    void BossMap::Generate()
    {
        Width = RandomInt(16, 24);
        Height = RandomInt(16, 24);

        BuildRoom(1, 1, Width - 2, Height - 2);
        RoundCorners();
        RemoveUnknownTiles();
        WrapWalls();

        for (int i = 2; i < Height - 2; i += 3)
        {
            GetTile(Width / 2 - 3, i)->Brazier = true;
            GetTile(Width / 2 - 3, i)->Walkable = false;
            GetTile(Width / 2 + 3, i)->Brazier = true;
            GetTile(Width / 2 + 3, i)->Walkable = false;
        }

        PlayerX = Width / 2;
        PlayerY = 1;
    }

    std::vector<std::unique_ptr<Actor>> BossMap::SpawnNPCs(int playerLevel)
    {
        std::vector<std::unique_ptr<Actor>> enemies;

        enemies.push_back(std::make_unique<Balrog>(Point{Width / 2, Height - 4}));

        return enemies;
    }

} // namespace cm