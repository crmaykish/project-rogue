#ifndef CM_RENDERER_H
#define CM_RENDERER_H

#include <string>
#include "cm_color.h"
#include "cm_assets.h"

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
        virtual float GetResolutionX() = 0;
        virtual float GetResolutionY() = 0;
        virtual void DrawRectangle(float x, float y, float w, float h, Color color) = 0;
        virtual void DrawTexture(AssetKey textureKey, float x, float y, float w, float h) = 0;
        virtual void DrawFont(std::string text, AssetKey fontKey, Color color, float x, float y) = 0;
    };
} // namespace cm

#endif // CM_RENDERER_H
