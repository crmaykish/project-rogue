#include "cm_renderer_sdl_gpu.h"
#include "cm_logger.h"

namespace cm
{
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
        GPU_Rectangle(gpu, x, y, x + w, y + h, {0xFF, 0x00, 0x00, 0xFF});
    }

} // namespace cm