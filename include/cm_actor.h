#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>

#include "cm_renderer.h"

namespace cm
{
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

    public:
        virtual ~Actor() {}
        virtual void Update() = 0;
        virtual void Step() = 0;
        virtual void Render(Renderer &renderer) = 0;
        virtual std::string GetName() = 0;
        float GetX() const;
        float GetY() const;
        void Move(int x, int y);

        bool IsActive();
        bool IsVisible();

        int GetHP();
        int GetMaxHP();
        void Damage(int damage);
    };

} // namespace cm

#endif // CM_ACTOR_H
