#include "cm_input.h"

namespace cm
{
    bool InputState::Once()
    {
        return On && !OnLast;
    }

    void InputState::Reset()
    {
        OnLast = On;
    }

    void MouseState::Reset()
    {
        Left.Reset();
        Middle.Reset();
        Right.Reset();
    }

    void UserInput::Reset()
    {
        Left.Reset();
        Right.Reset();
        Up.Reset();
        Down.Reset();
        Primary.Reset();
        Secondary.Reset();
        Activate.Reset();
        Quit.Reset();
        Mouse.Reset();
    }

} // namespace cm