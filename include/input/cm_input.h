#ifndef CM_INPUT_H
#define CM_INPUT_H

namespace cm
{
    struct InputState
    {
        bool On = false;
        bool OnLast = false;

        bool Once() const;
        void Reset();
    };

    struct MouseState
    {
        int X = 0;
        int Y = 0;
        InputState Left;
        InputState Right;
        InputState Middle;

        void Reset();
    };

    struct UserInput
    {
        MouseState Mouse;
        InputState Left;
        InputState Right;
        InputState Up;
        InputState Down;
        InputState Primary;
        InputState Secondary;
        InputState Activate;
        InputState Escape;
        InputState Quit;
        InputState Ability[4];
        InputState Num[10];

        void Reset();
    };

} // namespace cm

#endif // CM_INPUT_H
