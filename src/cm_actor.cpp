#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    void Actor::Move(float x, float y)
    {
        X += x;
        Y += y;
    }

    float Actor::GetX()
    {
        return X;
    }

    float Actor::GetY()
    {
        return Y;
    }

    bool Actor::IsActive()
    {
        return Active;
    }

    int Actor::GetHP()
    {
        return HP;
    }

    int Actor::GetMaxHP()
    {
        return MaxHP;
    }

    void Actor::Damage(int damage)
    {
        HP -= damage;

        Log("HP: " + std::to_string(HP) + " of " + std::to_string(MaxHP), LOG_INFO);

        if (HP <= 0)
        {
            Log("Target died", LOG_INFO);
            HP = 0;
            Active = false;
        }
    }

} // namespace cm
