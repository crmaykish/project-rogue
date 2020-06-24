#include "cm_game.h"
#include "cm_logger.h"
#include "cm_component_player_movement.h"
#include "cm_component_player_render.h"
#include "cm_component_enemy_render.h"
#include "cm_component_enemy_movement.h"

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

        MainCamera = std::make_shared<Camera>();

        MainRenderer->Init();
        MainRenderer->SetCamera(MainCamera);

        CurrentWorld = World::GenerateWorld(40, 24);

        // Create a player
        auto player = std::make_shared<Actor>(TILE_SIZE, TILE_SIZE);
        player->AttachMovementComponent(std::make_shared<PlayerMovementComponent>(player, Input));
        player->AttachRenderComponent(std::make_shared<PlayerRenderComponent>(player, MainRenderer));
        Actors.push_back(player);

        // Add an enemy
        auto enemy = std::make_shared<Actor>(7 * TILE_SIZE, 8 * TILE_SIZE);
        enemy->AttachRenderComponent(std::make_shared<EnemyRenderComponent>(enemy, MainRenderer));
        enemy->AttachMovementComponent(std::make_shared<EnemyMovementComponent>(enemy, CurrentWorld));
        Actors.push_back(enemy);

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
        if (Input.Quit.On)
        {
            Running = false;
        }

        // Update camera
        if (Input.Mouse.Left.Once())
        {
            mouseDownX = Input.Mouse.X + MainCamera->GetX();
            mouseDownY = Input.Mouse.Y + MainCamera->GetY();
        }
        else if (Input.Mouse.Left.On)
        {
            MainCamera->SetPosition(mouseDownX - Input.Mouse.X, mouseDownY - Input.Mouse.Y);
        }

        // Update the world
        CurrentWorld->Update();

        // TODO: this is a pretty hacky way to trigger a turn, make this more robust
        // maybe this belongs in the player code? Need a way to not step if the movement fails
        if (Input.Left.Once() || Input.Right.Once() || Input.Up.Once() || Input.Down.Once())
        {
            // Handle a turn of the game world
            CurrentWorld->Step();
        }

        // Update the actors
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

        // Render the world
        CurrentWorld->Render(MainRenderer);

        // Render the actors
        for (auto a : Actors)
        {
            a->Render();
        }

        // TODO: render the UI

        MainRenderer->Render();
    }

} // namespace cm
