#ifndef CM_RENDERER_H
#define CM_RENDERER_H

#include "cm_color.h"

namespace cm
{
    class Renderer
    {
    public:
        virtual ~Renderer() {}
        virtual void Init() = 0;
        virtual void Close() = 0;
        virtual void Prepare() = 0;
        virtual void Render() = 0;
        virtual void SetCameraPosition(float x, float y) = 0;
        virtual float GetCamX() = 0;
        virtual float GetCamY() = 0;

        virtual void DrawRectangle(float x, float y, float w, float h, Color color) = 0;
    };
} // namespace cm

#endif // CM_RENDERER_H
