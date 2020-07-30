#include "cm_game.h"
#include "cm_logger.h"
#include "cm_player.h"
#include "cm_renderer_sdl2.h"
#include "cm_input_handler_sdl.h"

namespace cm
{
    int fogX = 0;
    int fogY = 0;
    int frames = 0;

    void Game::Init()
    {
        Log("Initializing game...", LOG_INFO);

        srand(time(NULL));

        // Create world
        World = std::make_unique<GameWorld>(Input);

        // Create and assign input handler
        SetMainInputHandler(std::make_unique<cm::SDLInputHandler>());

        // Setup asset manager
        AssetManager = std::make_unique<Assets>();
        AssetManager->Init();

        // Setup renderer
        SetMainRenderer(std::make_unique<cm::SDL2Renderer>(*AssetManager));
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
        if (Input.Quit.On || Input.Escape.On)
        {
            Running = false;
        }

        // TODO: wrap this up in a rendering effects or post-processing class
        if (frames == 4)
        {
            fogX--;

            if (fogX == -256 * TileScaling)
            {
                fogX = 0;
            }

            frames = 0;
        }
        frames++;

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

        // Render background
        int bgTileSize = 48 * TileScaling;
        int col = 1 + (int)MainRenderer->GetResolutionX() / bgTileSize;
        int row = (int)MainRenderer->GetResolutionY() / bgTileSize;

        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < col; j++)
            {
                MainRenderer->DrawTexture(AssetKey::BackgroundTexture, bgTileSize * i, bgTileSize * j, bgTileSize, bgTileSize, true);
            }
        }

        // Render world objects
        World->Render(*MainRenderer);

        // Render fog
        int fogTileSize = 256 * TileScaling;
        col = 2 + (int)MainRenderer->GetResolutionX() / fogTileSize;
        row = 1 + (int)MainRenderer->GetResolutionY() / fogTileSize;

        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < col; j++)
            {
                MainRenderer->DrawTexture(AssetKey::FogTexture, fogX + fogTileSize * i, fogTileSize * j, fogTileSize, fogTileSize, true);
            }
        }

        RenderUI();

        // Render scanlines
        col = 1 + (int)MainRenderer->GetResolutionX() / TileSize;
        row = (int)MainRenderer->GetResolutionY() / TileSize;

        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < col; j++)
            {
                MainRenderer->DrawTexture(AssetKey::ScanlinesTexture, TileSize * i, TileSize * j, TileSize, TileSize, true);
            }
        }

        MainRenderer->Render();
    }

    void Game::SnapCameraToPlayer()
    {
        float camX = (World->GetPlayer()->Position.X * TileSize) - (MainRenderer->GetResolutionX() / 2) + (TileSize / 2);
        float camY = (MainRenderer->GetResolutionY() / 2) - (World->GetPlayer()->Position.Y * TileSize) - (TileSize / 2);
        MainRenderer->SetCameraPosition(camX, camY);
    }

    void Game::RenderUI()
    {
        int yOffset = MainRenderer->GetResolutionY();

        // Level number
        MainRenderer->DrawFont("Floor: " + std::to_string(World->GetLevelNumber()),
                               AssetKey::UIFont,
                               ColorWhite,
                               MainRenderer->GetResolutionX() - 120,
                               yOffset - 40,
                               0.6,
                               true);

        // Turn number
        MainRenderer->DrawFont("Turn: " + std::to_string(World->GetTurnNumber()),
                               AssetKey::UIFont,
                               ColorWhite,
                               MainRenderer->GetResolutionX() - 120,
                               yOffset - 80,
                               0.6,
                               true);

        // HP
        MainRenderer->DrawFont("HP: " + std::to_string(World->GetPlayer()->Stats.HP()) + " / " + std::to_string(World->GetPlayer()->Stats.MaxHP()),
                               AssetKey::UIFont,
                               ColorRed,
                               10,
                               yOffset - 40,
                               0.6,
                               true);

        yOffset -= 70;

        // Energy
        int energyX = 10;
        int energyY = yOffset;

        for (auto i = 0; i < World->GetPlayer()->Stats.Energy(); i++)
        {
            MainRenderer->DrawTexture(AssetKey::EnergyIcon, energyX, energyY, 24, 24, true);
            energyX += 32;
        }

        for (auto i = 0; i < World->GetPlayer()->Stats.MaxEnergy() - World->GetPlayer()->Stats.Energy(); i++)
        {
            MainRenderer->DrawTexture(AssetKey::EnergyEmptyIcon, energyX, energyY, 24, 24, true);
            energyX += 32;
        }

        yOffset -= 30;

        MainRenderer->DrawFont("VIT: " + std::to_string(World->GetPlayer()->Stats.GetStatValue(ActorStatType::Vitality)) +
                                   " | STR: " + std::to_string(World->GetPlayer()->Stats.GetStatValue(ActorStatType::Strength)),
                               AssetKey::UIFont,
                               ColorYellow,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        MainRenderer->DrawFont("DEX: " + std::to_string(World->GetPlayer()->Stats.GetStatValue(ActorStatType::Dexterity)) +
                                   " | INT: " + std::to_string(World->GetPlayer()->Stats.GetStatValue(ActorStatType::Intellect)),
                               AssetKey::UIFont,
                               ColorYellow,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        MainRenderer->DrawFont("ATK: " + std::to_string(World->GetPlayer()->Stats.GetAttackRating()) + " | DEF: " + std::to_string(World->GetPlayer()->Stats.GetDefenseRating()),
                               AssetKey::UIFont,
                               ColorPurple,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 60;

        int bX = MainRenderer->GetResolutionX() - (16 * TileScaling) - ((TileScaling * 2));
        int bY = (TileScaling * 2);

        auto items = World->GetPlayer()->InventoryComp.get();

        for (int i = 9; i > 0; i--)
        {
            MainRenderer->DrawTexture(AssetKey::ItemOutlineTexture, bX, bY, 16 * TileScaling, 16 * TileScaling, true);

            if (items->ItemAt(i - 1) != nullptr)
            {
                MainRenderer->DrawTexture(items->ItemAt(i - 1)->TextureKey, bX + (TileScaling * 2), bY + (TileScaling * 2), TileSize, TileSize, true);
            }

            MainRenderer->DrawFont(std::to_string(i),
                                   AssetKey::UIFont,
                                   ColorWhite,
                                   bX + (TileScaling * 2),
                                   bY,
                                   0.5,
                                   true);
            bX -= 16 * TileScaling + (TileScaling * 2);
        }

        // Equipped items

        int eqX = MainRenderer->GetResolutionX() - 10 - TileSize - 100;
        int eqY = MainRenderer->GetResolutionY() - TileSize * 2 - 64;

        auto &equipped = items->GetEquipment();
        for (auto const &[type, equipment] : equipped)
        {
            MainRenderer->DrawTexture(equipment->TextureKey, eqX, eqY, TileSize, TileSize, true);
            eqY -= (TileSize / 2);

            for (auto &s : equipment->StatModifiers)
            {
                MainRenderer->DrawFont(StatNames[s.GetStatType()] + ": " + (s.GetModifierType() == ActorStatModifierType::Add ? "+" : "x") + std::to_string((int)s.GetValue()),
                                       AssetKey::UIFont,
                                       ColorYellow,
                                       eqX,
                                       eqY,
                                       0.5,
                                       true);

                eqY -= TileSize / 2;
            }

            for (auto const &[trigger, effects] : equipment->Effects.Effects)
            {
                std::string label = trigger == EffectTrigger::Attack ? "Hit: " : "Defend: ";

                MainRenderer->DrawFont(label,
                                       AssetKey::UIFont,
                                       ColorWhite,
                                       eqX,
                                       eqY,
                                       0.5,
                                       true);

                eqY -= TileSize / 2;

                for (auto &ef : effects)
                {
                    MainRenderer->DrawFont(ef->GetName(),
                                           AssetKey::UIFont,
                                           ColorGreen,
                                           eqX,
                                           eqY,
                                           0.5,
                                           true);

                    eqY -= TileSize / 2;
                }
            }

            eqY -= TileSize / 2;
        }

        // Abilities
        int xAb = (TileScaling * 2);
        int yAb = (TileScaling * 2);

        auto abilities = World->GetPlayer()->AbilitiesComp.get();

        for (int i = 0; i < 4; i++)
        {
            auto a = abilities->AbilityAt(i);

            MainRenderer->DrawTexture(AssetKey::AbilityOutlineTexture, xAb, yAb, 16 * TileScaling, 16 * TileScaling, true);

            if (a != nullptr)
            {
                MainRenderer->DrawTexture(a->GetIcon(), xAb + (TileScaling * 2), yAb + (TileScaling * 2), TileSize, TileSize, true);

                // TODO: ugly
                std::string letter;
                switch (i)
                {
                case 0:
                    letter = "Z";
                    break;
                case 1:
                    letter = "X";
                    break;
                case 2:
                    letter = "C";
                    break;
                case 3:
                    letter = "V";
                    break;
                default:
                    break;
                }

                MainRenderer->DrawFont(letter, // TODO: show keys instead of numbers
                                       AssetKey::UIFont,
                                       ColorWhite,
                                       xAb + (TileScaling * 2),
                                       yAb,
                                       0.5,
                                       true);
            }

            xAb += 16 * TileScaling + (TileScaling * 2);
        }

        // Render combat log

        auto eventLog = World->GetEventLog();

        int eventLogX = 10;
        int eventLogY = 500;
        int eventLogMaxLines = 15;

        auto elem = eventLog.size() < eventLogMaxLines ? eventLog.begin() : eventLog.end() - eventLogMaxLines;

        while (elem != eventLog.end())
        {
            MainRenderer->DrawFont((*elem).event, AssetKey::UIFont, (*elem).color, eventLogX, eventLogY, 0.5, true);
            eventLogY -= 28;

            std::advance(elem, 1);
        }
    }

} // namespace cm
