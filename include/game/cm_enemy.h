#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Enemy : public Actor
    {
    private:
        AbilitySet Abilities;

    public:
        AssetKey Texture = AssetKey::Unknown;
        int BaseAttack = 0;
        int BaseDefense = 0;

        Enemy(int x, int y);
        void Update(GameWorld &world) override;
        void Render(const Renderer &renderer) override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(GameWorld &world) override;

        int GetAttack() override;
        int GetDefense() override;

        Inventory *GetInventory() override;
        AbilitySet *GetAbilitySet() override;
    };

    std::unique_ptr<Actor> Ghost(int x, int y, int level);
    std::unique_ptr<Actor> Flame(int x, int y, int level);
    std::unique_ptr<Actor> Skeleton(int x, int y, int level);
    std::unique_ptr<Actor> Spider(int x, int y, int level);
    std::unique_ptr<Actor> Slime(int x, int y, int level);
    std::unique_ptr<Actor> Mimic(int x, int y, int level);

    std::unique_ptr<Actor> RandomEnemy(int x, int y, int level);

} // namespace cm

#endif // CM_ENEMY_H
