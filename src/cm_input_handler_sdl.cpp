#include <SDL.h>
#include "cm_input_handler_sdl.h"

namespace cm
{
    static void HandleQuit(UserInput &userInput, const SDL_Event event);
    static void HandleMouse(UserInput &userInput, const SDL_Event event);
    static void HandleKeyboard(UserInput &userInput, const SDL_Event event);

    void SDLInputHandler::PollForInput(UserInput &userInput)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
        {
            HandleQuit(userInput, event);
            HandleMouse(userInput, event);
            HandleKeyboard(userInput, event);
        }
    }

    static void HandleQuit(UserInput &userInput, const SDL_Event event)
    {
        if (event.type == SDL_QUIT)
        {
            userInput.Quit.On = true;
        }
    }

    static void HandleMouse(UserInput &userInput, const SDL_Event event)
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&userInput.Mouse.X, &userInput.Mouse.Y);
            return;
        }

        bool clicked = false;

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            clicked = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            clicked = false;
        }
        else
        {
            return;
        }

        switch (event.button.button)
        {
        case SDL_BUTTON_LEFT:
            userInput.Mouse.Left.On = clicked;
            break;
        case SDL_BUTTON_RIGHT:
            userInput.Mouse.Right.On = clicked;
            break;
        case SDL_BUTTON_MIDDLE:
            userInput.Mouse.Middle.On = clicked;
        default:
            break;
        }
    }

    static void HandleKeyboard(UserInput &userInput, const SDL_Event event)
    {
        bool keyOn = false;

        if (event.type == SDL_KEYDOWN)
        {
            keyOn = true;
        }
        else if (event.type == SDL_KEYUP)
        {
            keyOn = false;
        }
        else
        {
            return;
        }

        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_LEFT:
            userInput.Left.On = keyOn;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            userInput.Right.On = keyOn;
            break;
        case SDLK_w:
        case SDLK_UP:
            userInput.Up.On = keyOn;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            userInput.Down.On = keyOn;
            break;
        case SDLK_SPACE:
            userInput.Primary.On = keyOn;
            break;
        case SDLK_e:
            userInput.Activate.On = keyOn;
            break;
        case SDLK_0:
            userInput.Num[0].On = keyOn;
            break;
        case SDLK_1:
            userInput.Num[1].On = keyOn;
            break;
        case SDLK_2:
            userInput.Num[2].On = keyOn;
            break;
        case SDLK_3:
            userInput.Num[3].On = keyOn;
            break;
        case SDLK_4:
            userInput.Num[4].On = keyOn;
            break;
        case SDLK_5:
            userInput.Num[5].On = keyOn;
            break;
        case SDLK_6:
            userInput.Num[6].On = keyOn;
            break;
        case SDLK_7:
            userInput.Num[7].On = keyOn;
            break;
        case SDLK_8:
            userInput.Num[8].On = keyOn;
            break;
        case SDLK_9:
            userInput.Num[9].On = keyOn;
            break;
        default:
            break;
        }
    }

} // namespace cm
