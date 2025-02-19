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

        void DecideNextAction(GameWorld &world);

    public:
        Player(const UserInput &input);
        void Update(GameWorld &world) override;
        void Tick(GameWorld &world) override;
        void Render(const Renderer &renderer) override;
        void Reset() override;

        bool ActionReady() override;
        std::unique_ptr<Action> NextAction(GameWorld &world) override;
    };

} // namespace cm

#endif // CM_PLAYER_H
