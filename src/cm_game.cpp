#include "cm_game.h"
#include "cm_logger.h"
#include "cm_component_player_movement.h"

namespace cm
{
    Game::Game()
    {
    }

    Game::~Game()
    {
    }

    void Game::Init()
    {
        Log("Initializing game...", LOG_INFO);

        MainRenderer->Init();

        auto player = std::make_shared<Actor>(TILE_SIZE, TILE_SIZE);
        player->AttachMovementComponent(std::make_shared<PlayerMovementComponent>(player, Input));
        Actors.push_back(player);

        Running = true;
    }

    void Game::Loop()
    {
        Log("Starting game loop", LOG_INFO);

        auto previousTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> lag;

        while (Running)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = currentTime - previousTime;
            previousTime = currentTime;
            lag += elapsedTime;

            // Check for user input
            if (MainInputHandler != nullptr)
            {
                MainInputHandler->PollForInput(Input);
            }

            while (lag >= TIME_PER_TICK)
            {
                if (Input.Quit.On)
                {
                    Running = false;
                }

                Update();

                // Input has been handled
                Input.Reset();

                lag -= TIME_PER_TICK;
            }

            Render();
        }
    }

    void Game::Close()
    {
        Log("Closing game...", LOG_INFO);

        MainRenderer->Close();
    }

    void Game::SetMainInputHandler(std::shared_ptr<InputHandler> mainInputHandler)
    {
        MainInputHandler = mainInputHandler;
    }

    void Game::SetMainRenderer(std::shared_ptr<Renderer> mainRenderer)
    {
        MainRenderer = mainRenderer;
    }

    void Game::Update()
    {
        for (auto a : Actors)
        {
            a->Update();
        }
    }

    void Game::Render()
    {
        if (MainRenderer == nullptr)
        {
            return;
        }

        MainRenderer->Prepare();

        for (auto a : Actors)
        {
            a->Render(MainRenderer);
        }

        MainRenderer->Render();
    }

} // namespace cm
