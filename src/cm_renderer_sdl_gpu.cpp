#include "cm_renderer_sdl_gpu.h"
#include "cm_logger.h"

namespace cm
{
    GPU_Rect SDLGPURenderer::FlipRect(const GPU_Rect r)
    {
        GPU_Rect flipped = r;
        flipped.y = ResolutionH - flipped.y - flipped.h;
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

    void SDLGPURenderer::DrawRectangle(float x, float y, float w, float h)
    {
        GPU_RectangleRoundFilled2(gpu, FlipRect({x, y, w, h}), 8, {0xAA, 0x10, 0x00, 0xFF});
    }

} // namespace cm