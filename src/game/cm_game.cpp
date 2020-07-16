#include "cm_game.h"
#include "cm_logger.h"
#include "cm_player.h"
#include "cm_renderer_sdl2.h"
#include "cm_input_handler_sdl.h"

namespace cm
{
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
        float camX = (World->GetPlayer()->Position.X * TileSize) - (MainRenderer->GetResolutionX() / 2) + (TileSize / 2);
        float camY = (MainRenderer->GetResolutionY() / 2) - (World->GetPlayer()->Position.Y * TileSize) - (TileSize / 2);
        MainRenderer->SetCameraPosition(camX, camY);
    }

    void Game::RenderUI()
    {
        int yOffset = MainRenderer->GetResolutionY() - 50;

        // Level number
        MainRenderer->DrawFont("Floor: " + std::to_string(World->GetLevelNumber()),
                               AssetKey::UIFont,
                               ColorWhite,
                               MainRenderer->GetResolutionX() - 120,
                               yOffset + 20,
                               0.6,
                               true);

        // Turn number
        MainRenderer->DrawFont("Turn: " + std::to_string(World->GetTurnNumber()),
                               AssetKey::UIFont,
                               ColorWhite,
                               MainRenderer->GetResolutionX() - 120,
                               yOffset - 20,
                               0.6,
                               true);

        // Player name
        MainRenderer->DrawFont(World->GetPlayer()->Name,
                               AssetKey::UIFont,
                               ColorWhite,
                               10,
                               yOffset,
                               1.0,
                               true);

        yOffset -= 30;

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

        // Level/experience
        MainRenderer->DrawFont("LVL: " + std::to_string(World->GetPlayer()->Level) + " | XP: " + std::to_string(World->GetPlayer()->Experience),
                               AssetKey::UIFont,
                               ColorGreen,
                               10,
                               yOffset,
                               0.6,
                               true);

        yOffset -= 30;

        // HP
        MainRenderer->DrawFont("HP: " + std::to_string(World->GetPlayer()->Stats.HP()) + " / " + std::to_string(World->GetPlayer()->Stats.MaxHP()),
                               AssetKey::UIFont,
                               ColorRed,
                               10,
                               yOffset,
                               0.6,
                               true);

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

        int bX = MainRenderer->GetResolutionX() - 48 - 6;
        int bY = 6;

        auto items = World->GetPlayer()->GetInventory();

        for (int i = 9; i > 0; i--)
        {
            MainRenderer->DrawTexture(AssetKey::ItemOutlineTexture, bX, bY, 48, 48, true);

            if (items->ItemAt(i - 1) != nullptr)
            {
                MainRenderer->DrawTexture(items->ItemAt(i - 1)->GetTextureKey(), bX + 6, bY + 6, TileSize, TileSize, true);
            }

            MainRenderer->DrawFont(std::to_string(i),
                                   AssetKey::UIFont,
                                   ColorWhite,
                                   bX + 6,
                                   bY,
                                   0.5,
                                   true);
            bX -= 48 + 6;
        }

        // Equipped items

        int eqX = MainRenderer->GetResolutionX() - 10 - TileSize;
        int eqY = MainRenderer->GetResolutionY() - TileSize * 2;

        auto weapon = items->EquipmentAt(ItemType::OneHand);
        if (weapon != nullptr)
        {
            MainRenderer->DrawTexture(weapon->GetTextureKey(), eqX, eqY, TileSize, TileSize, true);
            eqY -= (TileSize + 8);
        }

        auto offhand = items->EquipmentAt(ItemType::OffHand);
        if (offhand != nullptr)
        {
            MainRenderer->DrawTexture(offhand->GetTextureKey(), eqX, eqY, TileSize, TileSize, true);
            eqY -= (TileSize + 8);
        }

        auto helm = items->EquipmentAt(ItemType::Head);
        if (helm != nullptr)
        {
            MainRenderer->DrawTexture(helm->GetTextureKey(), eqX, eqY, TileSize, TileSize, true);
            eqY -= (TileSize + 8);
        }

        auto boots = items->EquipmentAt(ItemType::Boots);
        if (boots != nullptr)
        {
            MainRenderer->DrawTexture(boots->GetTextureKey(), eqX, eqY, TileSize, TileSize, true);
            eqY -= (TileSize + 8);
        }

        // Abilities
        int xAb = 6;
        int yAb = 6;

        auto abilities = World->GetPlayer()->GetAbilitySet();

        for (int i = 0; i < 4; i++)
        {
            auto a = abilities->AbilityAt(i);

            MainRenderer->DrawTexture(AssetKey::AbilityOutlineTexture, xAb, yAb, 48, 48, true);

            if (a != nullptr)
            {
                MainRenderer->DrawTexture(a->GetIcon(), xAb + 6, yAb + 6, TileSize, TileSize, true);

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
                                       xAb + 6,
                                       yAb,
                                       0.5,
                                       true);
            }

            xAb += 48 + 6;
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
