#ifndef CM_RENDERER_SDL2_H
#define CM_RENDERER_SDL2_H

#include <SDL2/SDL.h>
#include "cm_renderer.h"
#include "cm_assets.h"

namespace cm
{
    const int RESOLUTION_DEFAULT_W = 1280;
    const int RESOLUTION_DEFAULT_H = 800;
    const bool Fullscreen = true;

    class SDL2Renderer : public Renderer
    {
    private:
        SDL_Window *SDLWindow;
        SDL_Renderer *SDLRenderer;
        Assets &AssetManager;
        int ResolutionW = RESOLUTION_DEFAULT_W;
        int ResolutionH = RESOLUTION_DEFAULT_H;
        float CameraOffsetX = 0.0;
        float CameraOffsetY = 0.0;

        SDL_Rect TransformRect(float x, float y, float w, float h, bool absolute = false) const;

    public:
        SDL2Renderer(Assets &assetManager);
        void Init() override;
        void Close() override;
        void Prepare() override;
        void Render() override;
        void SetCameraPosition(float x, float y) override;
        float GetCamX() override;
        float GetCamY() override;
        float GetResolutionX() override;
        float GetResolutionY() override;

        void DrawRectangle(float x, float y, float w, float h, Color color) const override;
        void DrawTexture(AssetKey textureKey, float x, float y, float w, float h, bool absolute = true) const override;
        void DrawFont(std::string text, AssetKey fontKey, Color color, float x, float y, float scale = 1.0, bool absolute = false) const override;
    };

} // namespace cm

#endif /* CM_RENDERER_SDL2_H */
