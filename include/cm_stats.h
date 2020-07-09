#ifndef CM_STATS_H
#define CM_STATS_H

namespace cm
{
    enum struct DamageType
    {
        None,
        Physical,
        Fire,
        Frost,
        Poison,
    };

    struct Attack
    {
        DamageType Type = DamageType::Physical;
        int Value = 0;
    };

} // namespace cm

#endif // CM_STATS_H
