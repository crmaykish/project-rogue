#include <memory>
#include "cm_game.h"
#include "cm_input_handler_sdl.h"
#include "cm_renderer_sdl_gpu.h"

int main(int argv, char **args)
{
    cm::Game game;

    game.SetMainInputHandler(std::make_unique<cm::SDLInputHandler>());
    game.SetMainRenderer(std::make_unique<cm::SDLGPURenderer>());

    game.Init();
    game.Loop();
    game.Close();
}
