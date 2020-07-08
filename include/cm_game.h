#ifndef CM_GAME_H
#define CM_GAME_H

#include <memory>
#include <chrono>
#include "cm_input.h"
#include "cm_input_handler.h"
#include "cm_renderer.h"
#include "cm_game_world.h"
#include "cm_assets.h"

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

        std::unique_ptr<GameWorld> World;
        std::unique_ptr<InputHandler> MainInputHandler = nullptr;
        std::unique_ptr<Assets> AssetManager = nullptr;
        std::unique_ptr<Renderer> MainRenderer = nullptr;

        void Update();
        void Render();

        void RenderUI();

        void SnapCameraToPlayer();

    public:
        void Init();
        void Loop();
        void Close();

        void SetMainInputHandler(std::unique_ptr<InputHandler> mainInputHandler);
        void SetMainRenderer(std::unique_ptr<Renderer> mainRenderer);
    };

} // namespace cm

#endif // CM_GAME_H
