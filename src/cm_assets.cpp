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
        case AssetKey::UIFont:
            assetFileName = "game over.ttf";
            break;
        // Tiles
        case AssetKey::FloorTexture:
            assetFileName = "floor.png";
            break;
        case AssetKey::WallTexture:
            assetFileName = "wall.png";
            break;
        case AssetKey::DoorTexture:
            assetFileName = "door.png";
            break;
        // Actors
        case AssetKey::PlayerTexture:
            assetFileName = "player.png";
            break;
        case AssetKey::GhostTexture:
            assetFileName = "ghost.png";
            break;
        // Items
        case AssetKey::HealthPotionTexture:
            assetFileName = "potion_hp.png";
            break;
        default:
            Log("No file name found for asset key: " + std::to_string((int)key), LOG_WARNING);
            break;
        }

        return assetFileName;
    }

} // namespace cm