#ifndef CM_INPUT_HANDLER_H
#define CM_INPUT_HANDLER_H

#include "cm_input.h"

namespace cm
{
    class InputHandler
    {
    public:
        virtual void PollForInput(UserInput &userinput) = 0;
    };

} // namespace cm

#endif // CM_INPUT_HANDLER_H
