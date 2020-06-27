#include "cm_game.h"
#include "cm_logger.h"
#include "cm_player.h"
#include "cm_renderer_sdl_gpu.h"
#include "cm_input_handler_sdl.h"

namespace cm
{
    void Game::Init()
    {
        Log("Initializing game...", LOG_INFO);

        srand(time(NULL));

        // Create world
        World = std::make_unique<GameWorld>(40, 24);

        // Create and assign input handler
        SetMainInputHandler(std::make_unique<cm::SDLInputHandler>());

        // Setup asset manager
        AssetManager = std::make_unique<Assets>();
        AssetManager->Init();

        // Setup renderer        
        SetMainRenderer(std::make_unique<cm::SDLGPURenderer>(*AssetManager));
        MainRenderer->Init();

        // Create a player
        World->AddPlayer(std::make_shared<Player>(*World, Input));

        // TODO: kind of a hack
        World->Step();

        SnapCameraToPlayer();

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

        // Free movement of the camera
        if (Input.Mouse.Left.Once())
        {
            mouseDownX = Input.Mouse.X + MainRenderer->GetCamX();
            mouseDownY = Input.Mouse.Y + MainRenderer->GetCamY();
        }
        else if (Input.Mouse.Left.On)
        {
            MainRenderer->SetCameraPosition(mouseDownX - Input.Mouse.X, mouseDownY - Input.Mouse.Y);
        }

        World->Update();

        // TODO: this is a pretty hacky way to trigger a turn, make this more robust
        // maybe this belongs in the player code? Need a way to not step if the movement fails
        if (Input.Left.Once() || Input.Right.Once() || Input.Up.Once() || Input.Down.Once())
        {
            // Handle a turn of the game world
            World->Step();

            SnapCameraToPlayer();
        }
    }

    void Game::Render()
    {
        if (MainRenderer == nullptr)
        {
            return;
        }

        MainRenderer->Prepare();

        // Render world objects
        World->Render(*MainRenderer);

        // Render UI
        MainRenderer->DrawFont("ROGUE", AssetKey::UIFont, COLOR_WHITE, 0, 0);

        MainRenderer->Render();
        
    }

    void Game::SnapCameraToPlayer()
    {
        float camX = (World->GetPlayer().GetX() * TileSize) - (MainRenderer->GetResolutionX() / 2) + (TileSize / 2);
        float camY = (MainRenderer->GetResolutionY() / 2) - (World->GetPlayer().GetY() * TileSize) - (TileSize / 2);
        MainRenderer->SetCameraPosition(camX, camY);
    }

} // namespace cm
