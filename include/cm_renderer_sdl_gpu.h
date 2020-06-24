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
        float CameraOffsetX = 0.0;
        float CameraOffsetY = 0.0;

        GPU_Rect TransformRect(const GPU_Rect r);

    public:
        void Init() override;
        void Close() override;
        void Prepare() override;
        void Render() override;
        void SetCameraPosition(float x, float y) override;
        virtual float GetCamX() override;
        virtual float GetCamY() override;

        void DrawRectangle(float x, float y, float w, float h, Color color) override;
    };
} // namespace cm