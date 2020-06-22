#include <SDL_gpu.h>
#include "cm_renderer.h"

namespace cm
{
    const int RESOLUTION_DEFAULT_W = 1280;
    const int RESOLUTION_DEFAULT_H = 768;

    class SDLGPURenderer : public Renderer
    {
    private:
        GPU_Target *gpu;
        int ResolutionW = RESOLUTION_DEFAULT_W;
        int ResolutionH = RESOLUTION_DEFAULT_H;

        GPU_Rect FlipRect(const GPU_Rect r);

    public:
        void Init() override;
        void Close() override;
        void Prepare() override;
        void Render() override;

        void DrawRectangle(float x, float y, float w, float h) override;
    };
} // namespace cm