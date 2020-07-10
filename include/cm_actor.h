#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_game_world.h"
#include "cm_renderer.h"
#include "cm_action.h"
#include "cm_inventory.h"
#include "cm_abilities.h"

namespace cm
{
    // Forward Declarations
    class GameWorld;
    class Action;

    class Actor
    {
    public:
        std::string Name;
        bool Active = false;
        bool Visible = false;
        bool Friendly = false;
        int TileX = 0;
        int TileY = 0;
        int MaxHP = 0;
        int HP = 0;
        int MaxMana = 0;
        int Mana = 0;
        int Level = 1;
        int Experience = 0;

        int TorchFuel = 20;

        virtual ~Actor() {}

        // Game state changes
        virtual void Update(GameWorld &world) = 0;
        virtual void Render(const Renderer &renderer) = 0;
        virtual void Reset(){};

        // Actions
        virtual bool ActionReady() = 0;
        virtual std::unique_ptr<Action> NextAction(GameWorld &world) = 0;

        // Combat
        virtual int GetAttack() = 0;
        virtual int GetDefense() = 0;
        virtual void AddExperience(int killLevel){};

        // Items
        virtual Inventory *GetInventory() = 0;

        // Abilities
        virtual AbilitySet *GetAbilitySet() = 0;

        virtual int GetViewDistance() { return 0; }
    };

} // namespace cm

#endif // CM_ACTOR_H
