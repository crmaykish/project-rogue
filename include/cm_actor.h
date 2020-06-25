#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>

#include "cm_renderer.h"

namespace cm
{
    class Actor
    {
    protected:
        bool Active;
        int TileX = 0;
        int TileY = 0;

        // TODO: might be better to move the HP system into a component or at least into the subclasses
        int HP = 0;
        int MaxHP = 0;

    public:
        virtual ~Actor() {}
        virtual void Update() = 0;
        virtual void Render(Renderer &renderer) = 0;
        float GetX();
        float GetY();
        void Move(float x, float y);

        bool IsActive();

        int GetHP();
        int GetMaxHP();
        void Damage(int damage);
    };

} // namespace cm

#endif // CM_ACTOR_H
