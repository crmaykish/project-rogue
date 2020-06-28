#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>

#include "cm_renderer.h"
#include "cm_action.h"

#include "cm_item.h"

namespace cm
{
    const int InventorySize = 8;

    enum struct Faction
    {
        Human,
        Enemy
    };

    class Actor
    {
    protected:
        bool Active = false;
        bool Visible = false;
        int TileX = 0;
        int TileY = 0;
        // TODO: might be better to move the HP system into a component or at least into the subclasses
        int HP = 0;
        int MaxHP = 0;

        std::array<std::shared_ptr<Item>, InventorySize> Items;

    public:
        virtual ~Actor() {}

        virtual void Update() = 0;
        virtual void Render(Renderer &renderer) = 0;
        virtual std::shared_ptr<Action> NextAction() = 0;

        virtual Faction GetFaction() = 0;

        virtual std::string GetName() = 0;
        virtual int GetAttack() = 0;

        virtual void Reset() = 0;

        void SetPosition(int x, int y);
        float GetX() const;
        float GetY() const;
        void Move(int x, int y);

        bool IsActive();
        bool IsVisible();

        int GetHP();
        int GetMaxHP();
        void Damage(int damage);
        void Heal(int health);
    };

} // namespace cm

#endif // CM_ACTOR_H
