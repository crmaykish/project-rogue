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
        // Misc
        Unknown,
        // Fonts
        UIFont,
        // Interface
        ItemOutlineTexture,
        AbilityOutlineTexture,
        SelectedTileTexture,
        // Tiles
        FloorTexture,
        WallTexture,
        DoorTexture,
        TreeTexture,
        ChestTexture,
        // Actors
        KnightTexture,
        MageTexture,
        ArcherTexture,
        PriestTexture,
        GhostTexture,
        FlameTexture,
        SpiderTexture,
        SkeletonTexture,
        SlimeTexture,
        // Items
        HealthPotionTexture,
        EnergyPotionTexture,
        RejuvPotionTexture,
        TorchTexture,
        DaggerTexture,
        SwordGreyTexture,
        SwordBlueTexture,
        BootsLeatherTexture,
        HelmetLeatherTexture,
        BucklerTexture,
        ShieldTexture,
        BowTexture,
        CrossbowTexture,
        BookBlueTexture,
        AxeTexture,
        // Icons
        MeleeIcon,
        RangeIcon,
        FireballIcon,
        HealIcon,
        CleaveIcon,
    };

    class Assets
    {
    private:
        std::map<AssetKey, TTF_Font *> FontMap;
        std::map<AssetKey, GPU_Image *> TextureMap;

    public:
        void Init();
        void Close();

        TTF_Font *GetFont(AssetKey key);
        GPU_Image *GetTexture(AssetKey key);
    };

} // namespace cm

#endif // CM_ASSETS_H
