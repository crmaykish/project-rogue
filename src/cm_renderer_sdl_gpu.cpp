#include "cm_renderer_sdl_gpu.h"
#include "cm_logger.h"

namespace cm
{
    SDLGPURenderer::SDLGPURenderer(Assets &assetManager) : AssetManager(assetManager) {}

    GPU_Rect SDLGPURenderer::TransformRect(const GPU_Rect r, bool absolute)
    {
        GPU_Rect flipped = r;

        flipped.y = ResolutionH - flipped.y - flipped.h;

        // Offset everything by the camera position
        if (!absolute)
        {
            flipped.x -= CameraOffsetX;
            flipped.y -= CameraOffsetY;
        }

        return flipped;
    }

    void SDLGPURenderer::Init()
    {
        Log("Initializing SDL GPU renderer...", LOG_INFO);

        gpu = GPU_Init(ResolutionW, ResolutionH, GPU_DEFAULT_INIT_FLAGS);
    }

    void SDLGPURenderer::Close()
    {
        Log("Closing SDL GPU renderer...", LOG_INFO);
    }

    void SDLGPURenderer::Prepare()
    {
        GPU_Clear(gpu);
    }

    void SDLGPURenderer::Render()
    {
        GPU_Flip(gpu);
    }

    void SDLGPURenderer::SetCameraPosition(float x, float y)
    {
        CameraOffsetX = x;
        CameraOffsetY = y;
    }

    float SDLGPURenderer::GetCamX()
    {
        return CameraOffsetX;
    }

    float SDLGPURenderer::GetCamY()
    {
        return CameraOffsetY;
    }

    float SDLGPURenderer::GetResolutionX()
    {
        return ResolutionW;
    }

    float SDLGPURenderer::GetResolutionY()
    {
        return ResolutionH;
    }

    void SDLGPURenderer::DrawRectangle(float x, float y, float w, float h, Color color)
    {
        SDL_Color c = {color.red, color.green, color.blue, color.alpha};
        GPU_RectangleFilled2(gpu, TransformRect({x, y, w, h}), c);
    }

    void SDLGPURenderer::DrawTexture(AssetKey textureKey, float x, float y, float w, float h)
    {
        auto image = AssetManager.GetTexture(textureKey);
        GPU_Rect r = TransformRect({x, y, w, h});
        GPU_BlitRect(image, NULL, gpu, &r);
    }

    void SDLGPURenderer::DrawFont(std::string text, AssetKey fontKey, Color color, float x, float y, float scale, bool absolute)
    {
        SDL_Color fontColor = {color.red, color.green, color.blue, color.alpha};

        auto font = AssetManager.GetFont(fontKey);
        auto *surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
        auto *image = GPU_CopyImageFromSurface(surface);

        GPU_Rect textRect = TransformRect({x, y, (float)image->w * scale, (float)image->h * scale}, absolute);

        GPU_BlitRect(image, NULL, gpu, &textRect);

        GPU_FreeImage(image);
        SDL_FreeSurface(surface);
    }

} // namespace cm