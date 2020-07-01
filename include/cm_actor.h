#ifndef CM_ACTOR_H
#define CM_ACTOR_H

#include <memory>
#include "cm_game_world.h"
#include "cm_renderer.h"
#include "cm_action.h"
#include "cm_item.h"

namespace cm
{
    const int DefaultItemCountMax = 10;

    // Forward Declarations
    class GameWorld;
    class Action;

    class Actor
    {
    private:
        // TODO: wrap this up in an Inventory class
        int ItemCountMax = DefaultItemCountMax;
        std::vector<std::unique_ptr<Item>> Items;

    public:
        std::string Name;
        bool Active = false;
        bool Visible = false;
        bool Friendly = false;
        int TileX = 0;
        int TileY = 0;
        int MaxHP = 0;
        int HP = 0;

        virtual ~Actor() {}

        // Game state changes
        virtual void Update(const GameWorld &world) = 0;
        virtual void Render(const Renderer &renderer) = 0;
        virtual void Reset() = 0;

        virtual bool ActionReady() = 0;
        virtual std::unique_ptr<Action> NextAction(const GameWorld &world) = 0;

        // Combat
        virtual int GetAttack() = 0;

        // Inventory management
        void AddItem(std::unique_ptr<Item> item);
        void RemoveItem(int slot);
    };

} // namespace cm

#endif // CM_ACTOR_H
