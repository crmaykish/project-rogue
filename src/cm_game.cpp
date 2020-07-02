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
        World = std::make_unique<GameWorld>();

        // Create and assign input handler
        SetMainInputHandler(std::make_unique<cm::SDLInputHandler>());

        // Setup asset manager
        AssetManager = std::make_unique<Assets>();
        AssetManager->Init();

        // Setup renderer
        SetMainRenderer(std::make_unique<cm::SDLGPURenderer>(*AssetManager));
        MainRenderer->Init();

        // Create a player
        World->AddPlayer(std::make_shared<Player>(Input));

        World->Init();

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

        AssetManager->Close();
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

        World->Update();

        SnapCameraToPlayer();
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
        int yOffset = MainRenderer->GetResolutionY();

        MainRenderer->DrawFont(World->GetPlayer()->Name,
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset - 50,
                               1.0,
                               true);

        MainRenderer->DrawFont("HP: " + std::to_string(World->GetPlayer()->HP) + " / " + std::to_string(World->GetPlayer()->MaxHP),
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset - 80,
                               0.6,
                               true);

        MainRenderer->DrawFont("Attack: " + std::to_string(World->GetPlayer()->GetAttack()),
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset - 110,
                               0.6,
                               true);

        MainRenderer->DrawFont("Armor: " + std::to_string(0),
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset - 140,
                               0.6,
                               true);

        // TODO: this is hideous
        auto items = World->GetPlayer()->GetInventory();
        for (int i = 0; i < items->ItemCount(); i++)
        {
            MainRenderer->DrawFont(std::to_string(i) + ": " + items->ItemAt(i)->Name,
                                   AssetKey::UIFont,
                                   ColorRed,
                                   10,
                                   yOffset - 170 - (30 * i),
                                   0.6,
                                   true);
        }

        MainRenderer->Render();
    }

    void Game::SnapCameraToPlayer()
    {
        float camX = (World->GetPlayer()->TileX * TileSize) - (MainRenderer->GetResolutionX() / 2) + (TileSize / 2);
        float camY = (MainRenderer->GetResolutionY() / 2) - (World->GetPlayer()->TileY * TileSize) - (TileSize / 2);
        MainRenderer->SetCameraPosition(camX, camY);
    }

} // namespace cm
