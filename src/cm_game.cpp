#include "cm_game.h"
#include "cm_logger.h"
#include "cm_player.h"

namespace cm
{
    void Game::Init()
    {
        Log("Initializing game...", LOG_INFO);

        World = std::make_unique<GameWorld>(100, 40);

        MainRenderer->Init();

        // create a player
        auto player = std::make_unique<Player>(*World, Input, *MainRenderer);
        // World->AddActor();

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
                Update();

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

    void Game::SetMainInputHandler(std::unique_ptr<InputHandler> mainInputHandler)
    {
        MainInputHandler = std::move(mainInputHandler);
    }

    void Game::SetMainRenderer(std::unique_ptr<Renderer> mainRenderer)
    {
        MainRenderer = std::move(mainRenderer);
    }

    void Game::Update()
    {
        if (Input.Quit.On)
        {
            Running = false;
        }

        // Update camera
        if (Input.Mouse.Left.Once())
        {
            mouseDownX = Input.Mouse.X + MainRenderer->GetCamX();
            mouseDownY = Input.Mouse.Y + MainRenderer->GetCamY();
        }
        else if (Input.Mouse.Left.On)
        {
            MainRenderer->SetCameraPosition(mouseDownX - Input.Mouse.X, mouseDownY - Input.Mouse.Y);
        }

        // TODO: this is a pretty hacky way to trigger a turn, make this more robust
        // maybe this belongs in the player code? Need a way to not step if the movement fails
        if (Input.Left.Once() || Input.Right.Once() || Input.Up.Once() || Input.Down.Once())
        {
            // Handle a turn of the game world
            World->Step();
        }
    }

    void Game::Render()
    {
        if (MainRenderer == nullptr)
        {
            return;
        }

        MainRenderer->Prepare();

        World->Render(*MainRenderer);

        MainRenderer->Render();
    }

} // namespace cm
