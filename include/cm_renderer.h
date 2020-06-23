#ifndef CM_RENDERER_H
#define CM_RENDERER_H

#include <memory>
#include "cm_camera.h"

namespace cm
{
    class Renderer
    {
    public:
        virtual void Init() = 0;
        virtual void Close() = 0;
        virtual void Prepare() = 0;
        virtual void Render() = 0;

        virtual void SetCamera(std::shared_ptr<Camera> camera) = 0;

        virtual void DrawRectangle(float x, float y, float w, float h) = 0;
    };
} // namespace cm

#endif // CM_RENDERER_H
