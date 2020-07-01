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
        bool ActionReady = false;

    public:
        Player(const UserInput &input);
        void Update(const GameWorld &world) override;
        void Render(const Renderer &renderer) override;
        std::unique_ptr<Action> NextAction(const GameWorld &world) override;
        void Reset() override;

        int GetAttack() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
