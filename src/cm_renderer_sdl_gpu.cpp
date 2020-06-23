#include "cm_renderer_sdl_gpu.h"
#include "cm_logger.h"

namespace cm
{
    GPU_Rect SDLGPURenderer::TransformRect(const GPU_Rect r)
    {
        GPU_Rect flipped = r;

        flipped.y = ResolutionH - flipped.y - flipped.h;

        if (MainCamera != nullptr)
        {
            // Offset everything by the camera position
            flipped.x -= MainCamera->GetX();
            flipped.y -= MainCamera->GetY();
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

    void SDLGPURenderer::SetCamera(std::shared_ptr<Camera> camera)
    {
        MainCamera = camera;
    }

    void SDLGPURenderer::DrawRectangle(float x, float y, float w, float h, Color color)
    {
        SDL_Color c = {color.red, color.green, color.blue, color.alpha};
        GPU_RectangleRoundFilled2(gpu, TransformRect({x, y, w, h}), 8, c);
    }

} // namespace cm