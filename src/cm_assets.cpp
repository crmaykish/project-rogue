#include "cm_assets.h"
#include "cm_logger.h"

namespace cm
{
    void Assets::Init()
    {
        Log("Initializing asset manager...", LOG_INFO);

        if (TTF_Init() == -1)
        {
            Log("Failed to init TTF: " + std::string(TTF_GetError()), LOG_ERROR);
        }
    }

    std::shared_ptr<Font> Assets::GetFont(AssetKey key)
    {
        // TODO: check the font map before loading from file
        std::string assetFileName = AssetFileName(key);

        if (assetFileName.empty())
        {
            Log("Failed to load font: " + std::to_string((int)key), LOG_WARNING);
            return nullptr;
        }

        assetFileName = FontsPath + assetFileName;

        // Log("Loading font from file: " + assetFileName, LOG_INFO);

        auto f = TTF_OpenFont(assetFileName.c_str(), FontSize);
        auto font = std::make_shared<Font>(f);

        FontMap.insert({key, font});

        return font;
    }

    std::shared_ptr<Texture> Assets::GetTexture(AssetKey key)
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

        TextureMap.insert({key, std::make_shared<Texture>(t)});
        return TextureMap.find(key)->second;
    }

    std::string Assets::AssetFileName(AssetKey key)
    {
        std::string assetFileName;

        switch (key)
        {
        case AssetKey::UIFont:
            assetFileName = "game over.ttf";
            break;
        case AssetKey::FloorTexture:
            assetFileName = "floor.png";
            break;
        case AssetKey::WallTexture:
            assetFileName = "wall.png";
            break;
        case AssetKey::PlayerTexture:
            assetFileName = "player.png";
            break;
        case AssetKey::GhostTexture:
            assetFileName = "ghost.png";
            break;
        default:
            Log("No file name found for asset key: " + std::to_string((int)key), LOG_WARNING);
            break;
        }

        return assetFileName;
    }

} // namespace cm