#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
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
        // TODO: This class is overdue for some smaller components
        std::string Name;
        bool Active = false;
        bool Visible = false;
        bool Friendly = false;
        int TileX = 0;
        int TileY = 0;
        int TargetX = 0;
        int TargetY = 0;
        int TorchFuel = 0;
        int Level = 1;
        int Experience = 0;

        // Stats
        int MaxHP = 0;
        int HP = 0;
        int MaxMana = 0;
        int Mana = 0;

        int Vitality = 0;
        int Strength = 0;
        int Dexterity = 0;
        int Intellect = 0;

        virtual ~Actor() {}

        // Game state changes
        virtual void Update(GameWorld &world) = 0;
        virtual void Render(const Renderer &renderer) = 0;
        virtual void Reset(){};

        // Actions
        virtual bool ActionReady() = 0;
        virtual std::unique_ptr<Action> NextAction(GameWorld &world) = 0;

        // Combat
        int MeleeAttackRating()
        {
            return Level * Strength;
        }

        int RangedAttackRating()
        {
            return Level * Dexterity;
        }

        int DefenseRating()
        {
            return Level * Vitality;
        }

        void InitStats()
        {
            MaxHP = Level * Vitality * 1.2;
            HP = MaxHP;

            MaxMana = Level * Intellect * 0.8;
            Mana = MaxMana;
        }

        // Items
        virtual Inventory *GetInventory() = 0;

        // Abilities
        virtual AbilitySet *GetAbilitySet() = 0;

        virtual int GetViewDistance() { return 0; }
    };

} // namespace cm

#endif // CM_ACTOR_H
