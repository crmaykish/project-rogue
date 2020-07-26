#ifndef CM_ASSETS_H
#define CM_ASSETS_H

#include <memory>
#include <map>
#include <string>
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
        WallCrackedTexture,
        DoorTexture,
        DoorLockedTexture,
        TreeTexture,
        ChestTexture,
        WaterTexture,
        BridgeTexture,
        FireTexture,
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
        MimicTexture,
        SquidTexture,
        BalrogTexture,
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
        BattleAxeTexture,
        BeerTexture,
        BoneTexture,
        BottleTexture,
        ClubTexture,
        FalchionTexture,
        HammerTexture,
        ShieldTowerTexture,
        StaffTexture,
        WandBlueTexture,
        WandGreenTexture,
        WandRedTexture,
        WineTexture,
        CharmRedTexture,
        CharmBlueTexture,
        CharmGreenTexture,
        HelmetSteelTexture,
        BrazierTexture,
        KeyTexture,
        
        // Icons
        MeleeIcon,
        RangeIcon,
        FireballIcon,
        HealIcon,
        CleaveIcon,
        EnergyIcon,
        EnergyEmptyIcon,
        TeleportIcon,
    };

    class Assets
    {
    private:
        std::map<AssetKey, TTF_Font *> FontMap;
        std::map<AssetKey, SDL_Surface *> TextureMap;

    public:
        void Init();
        void Close();

        TTF_Font *GetFont(AssetKey key);
        SDL_Surface *GetTexture(AssetKey key);
    };

} // namespace cm

#endif // CM_ASSETS_H
