#ifndef CM_CAMERA_H
#define CM_CAMERA_H

namespace cm
{
    class Camera
    {
    private:
        float X = 0;
        float Y = 0;

    public:
        void SetPosition(float x, float y);
        void Move(float x, float y);

        float GetX();
        float GetY();
    };
} // namespace cm

#endif // CM_CAMERA_H
