#include <SDL_gpu.h>
#include <SDL_ttf.h>
#include "cm_renderer.h"
#include "cm_assets.h"

namespace cm
{
    const int RESOLUTION_DEFAULT_W = 800;
    const int RESOLUTION_DEFAULT_H = 600;

    class SDLGPURenderer : public Renderer
    {
    private:
        GPU_Target *gpu;
        Assets &AssetManager;
        int ResolutionW = RESOLUTION_DEFAULT_W;
        int ResolutionH = RESOLUTION_DEFAULT_H;
        float CameraOffsetX = 0.0;
        float CameraOffsetY = 0.0;

        GPU_Rect TransformRect(const GPU_Rect r, bool absolute = false);

    public:
        SDLGPURenderer(Assets &assetManager);
        void Init() override;
        void Close() override;
        void Prepare() override;
        void Render() override;
        void SetCameraPosition(float x, float y) override;
        float GetCamX() override;
        float GetCamY() override;
        float GetResolutionX() override;
        float GetResolutionY() override;

        void DrawRectangle(float x, float y, float w, float h, Color color) override;
        void DrawTexture(AssetKey textureKey, float x, float y, float w, float h) override;
        void DrawFont(std::string text, AssetKey fontKey, Color color, float x, float y, float scale = 1.0, bool absolute = false) override;
    };
} // namespace cm