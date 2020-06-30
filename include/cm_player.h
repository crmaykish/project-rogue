#ifndef CM_PLAYER_H
#define CM_PLAYER_H

#include "cm_actor.h"
#include "cm_game_world.h"
#include "cm_input.h"
#include "cm_renderer.h"

namespace cm
{
    class Player : public Actor
    {
    private:
        GameWorld &World;
        UserInput &Input;

    public:
        Player(GameWorld &world, UserInput &input);

        void Update() override;
        std::unique_ptr<Action> NextAction() override;
        void Render(Renderer &renderer) override;

        int GetAttack() override;
        std::string GetName() override;
        Faction GetFaction() override;

        void Reset() override;
    };

} // namespace cm

#endif // CM_PLAYER_H
