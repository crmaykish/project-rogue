#include <memory>
#include "cm_game.h"

int main(int argv, char **args)
{
    cm::Game game;

    game.Init();
    game.Loop();
    game.Close();
}
