#include "cm_effect.h"
#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    // Damage
    DamageEffect::DamageEffect(int damage) : Damage(damage) {}

    void DamageEffect::Use(Actor *source, Actor *dest, GameWorld *world)
    {
        source->HP -= Damage;

        if (source->HP <= 0)
        {
            source->HP = 0;

            if (!source->Friendly)
            {
                source->Active = false;
            }
        }
    }

    // Heal
    HealEffect::HealEffect(int health) : Health(health) {}

    void HealEffect::Use(Actor *source, Actor *dest, GameWorld *world)
    {
        Log("healing for: " + std::to_string(Health), LOG_INFO);

        source->HP += Health;

        if (source->HP > source->MaxHP)
        {
            source->HP = source->MaxHP;
        }
    }

    // Torch Fuel
    void AddTorchFuelEffect::Use(Actor *source, Actor *dest, GameWorld *world)
    {
        if (source->Friendly)
        {
            source->TorchFuel += 10;
        }
    }

} // namespace cm