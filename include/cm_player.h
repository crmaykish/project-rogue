#ifndef CM_PLAYER_H
#define CM_PLAYER_H

#include "cm_actor.h"
#include "cm_input.h"

namespace cm
{
    class Player : public Actor
    {
    private:
        const UserInput &Input;
        std::unique_ptr<Action> nextAction;
        Inventory Items;

        void DecideNextAction(const GameWorld &world);

    public:
        Player(const UserInput &input);
        void Update(const GameWorld &world) override;
        void Render(const Renderer &renderer) override;
        void Reset() override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(const GameWorld &world) override;

        int GetAttack() override;

        Inventory *GetInventory() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
