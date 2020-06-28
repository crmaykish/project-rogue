#ifndef CM_ASSETS_H
#define CM_ASSETS_H

#include <memory>
#include <map>
#include <string>

// It would be nice if the asset manager was independent of the SDL implementation,
// but that's probably over-designing at this point
// If that's ever a need, refactor this class into an interface and implement an
// SDLAssetManager class
#include <SDL_gpu.h>
#include <SDL_ttf.h>

namespace cm
{
    const std::string AssetsPath = "assets/";
    const std::string FontsPath = AssetsPath;

    const int FontSize = 64;

    enum struct AssetKey
    {
        // Fonts
        UIFont,
        // Tiles
        FloorTexture,
        WallTexture,
        DoorTexture,
        // Actors
        PlayerTexture,
        GhostTexture,
        // Items
        HealthPotionTexture,
        EnergyPotionTexture,
        RejuvPotionTexture,
        TorchTexture,
    };

    class Font
    {
    private:
        TTF_Font *TTFFont;

    public:
        Font(TTF_Font *ttfFont)
        {
            TTFFont = ttfFont;
        }
        ~Font()
        {
            TTF_CloseFont(TTFFont);
        }
        TTF_Font *GetTTFFont()
        {
            return TTFFont;
        }
    };

    class Texture
    {
    private:
        GPU_Image *GPUImage;

    public:
        Texture(GPU_Image *gpuImage)
        {
            GPUImage = gpuImage;
        };
        ~Texture()
        {
            GPU_FreeImage(GPUImage);
        }
        GPU_Image *GetGPUImage()
        {
            return GPUImage;
        }
    };

    class Assets
    {
    private:
        // TODO: can we get away with not storing shared pointers here?
        std::map<AssetKey, std::shared_ptr<Font>> FontMap;
        std::map<AssetKey, std::shared_ptr<Texture>> TextureMap;

        std::string AssetFileName(AssetKey key);

    public:
        void Init();

        std::shared_ptr<Font> GetFont(AssetKey key);
        std::shared_ptr<Texture> GetTexture(AssetKey key);
    };
} // namespace cm

#endif // CM_ASSETS_H
