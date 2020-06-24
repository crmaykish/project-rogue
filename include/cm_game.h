#ifndef CM_GAME_H
#define CM_GAME_H

#include <memory>
#include <vector>
#include <chrono>
#include "cm_input.h"
#include "cm_input_handler.h"
#include "cm_renderer.h"
#include "cm_actor.h"
#include "cm_world.h"

namespace cm
{
    // Rate at which the game state is updated (not the framerate)
    const double TICK_RATE_HZ = 60;
    const auto TIME_PER_TICK = std::chrono::duration<double>(1.0 / TICK_RATE_HZ);

    class Game
    {
    private:
        bool Running = false;
        UserInput Input;

        int mouseDownX = 0;
        int mouseDownY = 0;

        std::unique_ptr<InputHandler> MainInputHandler = nullptr;
        std::unique_ptr<Renderer> MainRenderer = nullptr;
        std::unique_ptr<World> CurrentWorld = nullptr;

        std::vector<std::shared_ptr<Actor>> Actors;

        void Update();
        void Render();

    public:
        Game();
        ~Game();

        void Init();
        void Loop();
        void Close();

        void SetMainInputHandler(std::unique_ptr<InputHandler> mainInputHandler);
        void SetMainRenderer(std::unique_ptr<Renderer> mainRenderer);
    };

} // namespace cm

#endif // CM_GAME_H
