#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    void Actor::Move(int x, int y)
    {
        TileX += x;
        TileY += y;
    }

    void Actor::SetPosition(int x, int y)
    {
        TileX = x;
        TileY = y;
    }

    float Actor::GetX() const
    {
        return TileX;
    }

    float Actor::GetY() const
    {
        return TileY;
    }

    bool Actor::IsActive()
    {
        return Active;
    }

    bool Actor::IsVisible()
    {
        return Visible;
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

        if (HP <= 0)
        {
            HP = 0;
            Active = false;
        }
    }

    void Actor::Heal(int health)
    {
        HP += health;

        if (HP >= MaxHP)
        {
            HP = MaxHP;
        }
    }

} // namespace cm
