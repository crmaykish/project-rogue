#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_renderer.h"
#include "cm_action.h"
#include "cm_inventory.h"
#include "cm_abilities.h"
#include "cm_actor_stat.h"
#include "cm_math.h"

namespace cm
{
    // Forward Declarations
    class GameWorld;
    class Action;

    class Actor
    {
    public:
        // TODO: This class is overdue for some smaller components
        std::string Name;
        bool Active = false;
        bool Visible = false;
        bool Friendly = false;
        Point Position;
        Point Target;
        int TorchFuel = 0;
        int Level = 1;
        int Experience = 0;

        // Stats
        // TODO: move hp and mana into the stats system
        int MaxHP = 0;
        int HP = 0;
        int MaxMana = 0;
        int Mana = 0;

        // TODO: hide this behind a virtual function if any actors don't have stats
        ActorStatSet Stats;

        virtual ~Actor() {}

        // Game state changes
        virtual void Update(GameWorld &world) = 0;
        virtual void Render(const Renderer &renderer) = 0;
        virtual void Reset(){};

        // Actions
        virtual bool ActionReady() = 0;
        virtual std::unique_ptr<Action> NextAction(GameWorld &world) = 0;

        // Items
        virtual Inventory *GetInventory() = 0;

        // Abilities
        virtual AbilitySet *GetAbilitySet() = 0;

        virtual int GetViewDistance() { return 0; }
    };

    int ActorDistance(Actor &a, Actor &b);

} // namespace cm

#endif // CM_ACTOR_H
