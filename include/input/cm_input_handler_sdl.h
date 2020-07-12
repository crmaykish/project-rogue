#ifndef CM_INPUT_HANDLER_SDL_H
#define CM_INPUT_HANDLER_SDL_H

#include "cm_input_handler.h"

namespace cm
{
    class SDLInputHandler : public InputHandler
    {
    public:
        void PollForInput(UserInput &userinput) override;
    };

} // namespace cm

#endif // CM_INPUT_HANDLER_SDL_H
