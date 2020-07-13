#include "cm_input.h"

namespace cm
{
    bool InputState::Once() const
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
        Escape.Reset();
        Quit.Reset();
        Mouse.Reset();

        for (auto &a : Ability)
        {
            a.Reset();
        }

        for (auto &n : Num)
        {
            n.Reset();
        }
    }

} // namespace cm