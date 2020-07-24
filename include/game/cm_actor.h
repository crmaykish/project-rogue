#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_renderer.h"
#include "cm_action.h"
#include "cm_inventory.h"
#include "cm_abilities.h"
#include "cm_actor_stat.h"
#include "cm_effect.h"
#include "cm_combat.h"
#include "cm_math.h"

namespace cm
{
    class GameWorld;
    class Action;

    class Actor
    {
    public:
        std::string Name;

        // Flags
        bool Active = false;
        bool Visible = false;
        bool Friendly = false;
        bool TurnFinished = false;

        // Location
        Point Position;
        Point Target;

        // Stats
        ActorStatSet Stats;
        int Level = 1;
        int Experience = 0;

        // Components
        std::unique_ptr<Inventory> InventoryComp = nullptr;
        std::unique_ptr<AbilitySet> AbilitiesComp = nullptr;
        std::unique_ptr<EffectComponent> EffectsComp = nullptr;
        std::unique_ptr<Combat> CombatComp = nullptr;

        virtual ~Actor() {}

        // Game state changes
        virtual void Update(GameWorld &world) = 0;
        virtual void Tick(GameWorld &world) = 0;
        virtual void Render(const Renderer &renderer) = 0;
        virtual void Reset(){};

        // Actions
        virtual bool ActionReady() = 0;
        virtual std::unique_ptr<Action> NextAction(GameWorld &world) = 0;

        virtual int GetViewDistance() { return 0; }
    };

} // namespace cm

#endif // CM_ACTOR_H
