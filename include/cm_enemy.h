#ifndef CM_ENEMY_H
#define CM_ENEMY_H

#include "cm_actor.h"

namespace cm
{
    class Enemy : public Actor
    {
    public:
        Enemy(float x, float y);
        void Update() override;
        void Render() override;
    };

} // namespace cm

#endif // CM_ENEMY_H
