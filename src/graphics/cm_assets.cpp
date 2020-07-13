#include "cm_assets.h"
#include "cm_logger.h"

namespace cm
{
    // Local function prototypes
    std::string AssetFileName(AssetKey key);

    void Assets::Init()
    {
        Log("Initializing asset manager...", LOG_INFO);

        if (TTF_Init() == -1)
        {
            Log("Failed to init TTF: " + std::string(TTF_GetError()), LOG_ERROR);
        }
    }

    void Assets::Close()
    {
        Log("Closing asset manager", LOG_INFO);

        for (auto font : FontMap)
        {
            TTF_CloseFont(font.second);
        }

        for (auto texture : TextureMap)
        {
            GPU_FreeImage(texture.second);
        }
    }

    TTF_Font *Assets::GetFont(AssetKey key)
    {
        auto fontIt = FontMap.find(key);

        if (fontIt != FontMap.end())
        {
            return fontIt->second;
        }

        std::string assetFileName = AssetFileName(key);

        if (assetFileName.empty())
        {
            Log("Failed to load font: " + std::to_string((int)key), LOG_WARNING);
            return nullptr;
        }

        assetFileName = FontsPath + assetFileName;

        Log("Loading font from file: " + assetFileName, LOG_INFO);

        auto f = TTF_OpenFont(assetFileName.c_str(), FontSize);

        FontMap.insert({key, f});

        return FontMap.find(key)->second;
    }

    GPU_Image *Assets::GetTexture(AssetKey key)
    {
        auto textureIt = TextureMap.find(key);

        if (textureIt != TextureMap.end())
        {
            return textureIt->second;
        }

        auto assetFileName = AssetFileName(key);

        if (assetFileName.empty())
        {
            Log("Failed to load texture: " + std::to_string((int)key), LOG_WARNING);
            return nullptr;
        }

        assetFileName = FontsPath + assetFileName;

        Log("Loading texture from file: " + assetFileName, LOG_INFO);
        auto t = GPU_LoadImage(assetFileName.c_str());

        TextureMap.insert({key, t});
        return TextureMap.find(key)->second;
    }

    std::string AssetFileName(AssetKey key)
    {
        std::string assetFileName;

        switch (key)
        {
        case AssetKey::Unknown:
            assetFileName = "error.png";
            break;
        case AssetKey::UIFont:
            assetFileName = "EXEPixelPerfect.ttf";
            break;

        // Interface
        case AssetKey::ItemOutlineTexture:
            assetFileName = "item_outline.png";
            break;
        case AssetKey::AbilityOutlineTexture:
            assetFileName = "ability_outline.png";
            break;
        case AssetKey::SelectedTileTexture:
            assetFileName = "tile_outline.png";
            break;

        // Tiles
        case AssetKey::FloorTexture:
            assetFileName = "floor.png";
            break;
        case AssetKey::WallTexture:
            assetFileName = "wall.png";
            break;
        case AssetKey::WallCrackedTexture:
            assetFileName = "wall_cracked.png";
            break;
        case AssetKey::DoorTexture:
            assetFileName = "door.png";
            break;
        case AssetKey::TreeTexture:
            assetFileName = "tree.png";
            break;
        case AssetKey::ChestTexture:
            assetFileName = "chest.png";
            break;

        // Actors
        case AssetKey::KnightTexture:
            assetFileName = "knight.png";
            break;
        case AssetKey::MageTexture:
            assetFileName = "mage.png";
            break;
        case AssetKey::ArcherTexture:
            assetFileName = "archer.png";
            break;
        case AssetKey::PriestTexture:
            assetFileName = "priest.png";
            break;
        case AssetKey::GhostTexture:
            assetFileName = "ghost.png";
            break;
        case AssetKey::FlameTexture:
            assetFileName = "flame.png";
            break;
        case AssetKey::SpiderTexture:
            assetFileName = "spider.png";
            break;
        case AssetKey::SkeletonTexture:
            assetFileName = "skeleton.png";
            break;
        case AssetKey::SlimeTexture:
            assetFileName = "slime_green.png";
            break;
        case AssetKey::MimicTexture:
            assetFileName = "mimic.png";
            break;

        // Items
        case AssetKey::HealthPotionTexture:
            assetFileName = "potion_hp.png";
            break;
        case AssetKey::TorchTexture:
            assetFileName = "torch.png";
            break;
        case AssetKey::DaggerTexture:
            assetFileName = "dagger_rusty.png";
            break;
        case AssetKey::SwordGreyTexture:
            assetFileName = "sword_grey.png";
            break;
        case AssetKey::SwordBlueTexture:
            assetFileName = "sword_blue.png";
            break;
        case AssetKey::BootsLeatherTexture:
            assetFileName = "boots_leather.png";
            break;
        case AssetKey::HelmetLeatherTexture:
            assetFileName = "helmet_leather.png";
            break;
        case AssetKey::BucklerTexture:
            assetFileName = "buckler.png";
            break;
        case AssetKey::ShieldTexture:
            assetFileName = "shield.png";
            break;
        case AssetKey::BowTexture:
            assetFileName = "bow.png";
            break;
        case AssetKey::CrossbowTexture:
            assetFileName = "crossbow.png";
            break;
        case AssetKey::BookBlueTexture:
            assetFileName = "book_blue.png";
            break;
        case AssetKey::AxeTexture:
            assetFileName = "axe.png";
            break;
        case AssetKey::BattleAxeTexture:
            assetFileName = "axe_battle.png";
            break;
        case AssetKey::BeerTexture:
            assetFileName = "beer.png";
            break;
        case AssetKey::BoneTexture:
            assetFileName = "bone.png";
            break;
        case AssetKey::BottleTexture:
            assetFileName = "bottle.png";
            break;
        case AssetKey::ClubTexture:
            assetFileName = "club.png";
            break;
        case AssetKey::FalchionTexture:
            assetFileName = "falchion.png";
            break;
        case AssetKey::HammerTexture:
            assetFileName = "hammer.png";
            break;
        case AssetKey::ShieldTowerTexture:
            assetFileName = "shield_tower.png";
            break;
        case AssetKey::StaffTexture:
            assetFileName = "staff.png";
            break;
        case AssetKey::WandBlueTexture:
            assetFileName = "wand_blue.png";
            break;
        case AssetKey::WandGreenTexture:
            assetFileName = "wand_green.png";
            break;
        case AssetKey::WandRedTexture:
            assetFileName = "wand_red.png";
            break;
        case AssetKey::WineTexture:
            assetFileName = "wine.png";
            break;
        case AssetKey::CharmRedTexture:
            assetFileName = "charm_red.png";
            break;
        case AssetKey::CharmBlueTexture:
            assetFileName = "charm_blue.png";
            break;
        case AssetKey::CharmGreenTexture:
            assetFileName = "charm_green.png";
            break;

        // Icons
        case AssetKey::MeleeIcon:
            assetFileName = "icon_melee.png";
            break;
        case AssetKey::RangeIcon:
            assetFileName = "icon_range.png";
            break;
        case AssetKey::FireballIcon:
            assetFileName = "icon_fireball.png";
            break;
        case AssetKey::HealIcon:
            assetFileName = "icon_heal.png";
            break;
        case AssetKey::CleaveIcon:
            assetFileName = "icon_cleave.png";
            break;

        default:
            Log("No file name found for asset key: " + std::to_string((int)key), LOG_WARNING);
            break;
        }

        return assetFileName;
    }

} // namespace cm