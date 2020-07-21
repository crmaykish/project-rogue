#ifndef CM_EFFECT_H
#define CM_EFFECT_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace cm
{
    class Actor;
    class GameWorld;

    // TODO: one big master list of effects, everything just takes pointers to them? easy to map and hand out keys
    // that works as long as effects are all stateless and can be shared across uses

    enum struct EffectTrigger
    {
        Action,  /**< Effect is triggered when the owner makes any action */
        UseItem, /**< Effect is triggered when the owner uses an item with this effect attached, i.e. not just using any random item */
        Attack,  /**< Effect is triggered when the owner attacks a target */
        Defend,  /**< Effect is triggered when the owner takes damage */
        Kill,    /**< Effect is triggered when the owner kills a target */
        Die,     /**< Effect is triggered when the owner dies */
    };

    class Effect
    {
    protected:
        uint32_t Id = 0;

    public:
        Effect();
        virtual ~Effect() {}
        virtual void Use(Actor *source, Actor *target, GameWorld *world) = 0;
        virtual std::string GetName() = 0;
        uint32_t GetId();
    };

    class EffectMap
    {
    public:
        std::unordered_map<EffectTrigger, std::vector<std::shared_ptr<Effect>>> Effects;
        void Add(EffectTrigger trigger, std::shared_ptr<Effect> effect);
        void Remove(uint32_t effectId);
    };

    class EffectComponent : public EffectMap
    {
    public:
        void TriggerEffects(EffectTrigger trigger, Actor *source, Actor *target, GameWorld *world);
    };

    // Effects

    class RetaliationEffect : public Effect
    {
    public:
        std::string GetName() override { return "Retaliation"; }
        void Use(Actor *source, Actor *target, GameWorld *world) override;
    };

    class ExplosionEffect : public Effect
    {
    public:
        std::string GetName() override { return "Explosion"; }
        void Use(Actor *source, Actor *target, GameWorld *world) override;
    };

    class LifeStealEffect : public Effect
    {
    public:
        std::string GetName() override { return "Life Steal"; }
        void Use(Actor *source, Actor *target, GameWorld *world) override;
    };

    class HealEffect : public Effect
    {
    public:
        std::string GetName() override { return "Healing"; }
        void Use(Actor *source, Actor *target, GameWorld *world) override;
    };

    class SacrificeEffect : public Effect
    {
    public:
        std::string GetName() override { return "Sacrifice"; }
        void Use(Actor *source, Actor *target, GameWorld *world) override;
    };

} // namespace cm

#endif // CM_EFFECT_H
