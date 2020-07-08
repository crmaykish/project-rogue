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

        RenderUI();

        MainRenderer->Render();
    }

    void Game::SnapCameraToPlayer()
    {
        float camX = (World->GetPlayer()->TileX * TileSize) - (MainRenderer->GetResolutionX() / 2) + (TileSize / 2);
        float camY = (MainRenderer->GetResolutionY() / 2) - (World->GetPlayer()->TileY * TileSize) - (TileSize / 2);
        MainRenderer->SetCameraPosition(camX, camY);
    }

    void Game::RenderUI()
    {
        int yOffset = MainRenderer->GetResolutionY() - 50;

        MainRenderer->DrawFont(World->GetPlayer()->Name,
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset,
                               1.0,
                               true);

        yOffset -= 30;

        MainRenderer->DrawFont(std::to_string(World->GetPlayer()->HP) + " / " + std::to_string(World->GetPlayer()->MaxHP),
                               AssetKey::UIFont,
                               ColorRed,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        MainRenderer->DrawFont(std::to_string(40) + " / " + std::to_string(40),
                               AssetKey::UIFont,
                               ColorBlue,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        MainRenderer->DrawFont(std::to_string(World->GetPlayer()->TorchFuel) + " / " + std::to_string(40),
                               AssetKey::UIFont,
                               ColorYellow,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        yOffset -= 8;

        // Inventory
        // TODO: this is hideous
        auto items = World->GetPlayer()->GetInventory();
        for (int i = 0; i < items->ItemCount(); i++)
        {
            MainRenderer->DrawTexture(items->ItemAt(i)->GetTextureKey(), 10, yOffset, TileSize, TileSize, true);
            MainRenderer->DrawFont(std::to_string(i) + ": " + items->ItemAt(i)->Name,
                                   AssetKey::UIFont,
                                   ColorGreen,
                                   10 + 10 + TileSize,
                                   yOffset + 4,
                                   0.6,
                                   true);

            yOffset -= (TileSize + 8);
        }

        // TODO: show all equipped weapons

        // Equipped Items
        auto mainWeapon = items->EquipmentAt(ItemType::OneHand);

        if (mainWeapon != nullptr)
        {
            MainRenderer->DrawTexture(mainWeapon->GetTextureKey(), 10, yOffset, TileSize, TileSize);

            MainRenderer->DrawFont(mainWeapon->Name,
                                   AssetKey::UIFont,
                                   ColorBlue,
                                   TileSize + 20,
                                   yOffset,
                                   0.6,
                                   true);
        }
    }

} // namespace cm
