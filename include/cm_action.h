#ifndef CM_ACTION_H
#define CM_ACTION_H

namespace cm
{
    class Action
    {
    public:
        virtual void Execute() = 0;
    };
    
} // namespace cm

#endif // CM_ACTION_H
