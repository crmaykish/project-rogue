#include <unordered_map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "cm_renderer_sdl2.h"
#include "cm_logger.h"

namespace cm
{
    const std::string WINDOW_TITLE = "Project Rogue";

    static std::unordered_map<AssetKey, SDL_Texture *> textureMap;

    SDL2Renderer::SDL2Renderer(Assets &assetManager) : AssetManager(assetManager) {}

    SDL_Rect SDL2Renderer::TransformRect(float x, float y, float w, float h, bool absolute) const
    {
        SDL_Rect flipped = {static_cast<int>(x),
                            static_cast<int>(y),
                            static_cast<int>(w),
                            static_cast<int>(h)};

        flipped.y = ResolutionH - flipped.y - flipped.h;

        // Offset everything by the camera position
        if (!absolute)
        {
            flipped.x -= CameraOffsetX;
            flipped.y -= CameraOffsetY;
        }

        return flipped;
    }

    void SDL2Renderer::Init()
    {
        Log("Initializing SDL2 renderer...", LOG_INFO);

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
        {
            Log("Failed to initialize SDL: " + std::string(SDL_GetError()), LOG_ERROR);
            exit(1);
        }

        if (TTF_Init() != 0)
        {
            Log("Failed to initialize TTF: " + std::string(TTF_GetError()), LOG_ERROR);
            exit(1);
        }

        if (IMG_Init(IMG_INIT_PNG) == 0)
        {
            Log("Failed to initialize IMG: " + std::string(IMG_GetError()), LOG_ERROR);
            exit(1);
        }

        if (Mix_Init(MIX_INIT_MOD | MIX_INIT_MP3) == 0)
        {
            Log("Failed to initialize Mixer: " + std::string(Mix_GetError()), LOG_ERROR);
            exit(1);
        }

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

        // Create the SDL Window
        SDLWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     ResolutionW, ResolutionH,
                                     SDL_WINDOW_SHOWN);

        if (SDLWindow == NULL)
        {
            Log("Failed to create SDL window: " + std::string(SDL_GetError()), LOG_ERROR);
            exit(1);
        }

        // Create an SDL renderer and attach it to the window
        SDLRenderer = SDL_CreateRenderer(SDLWindow,
                                         -1,
                                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (SDLRenderer == NULL)
        {
            Log("Failed to create SDL renderer: " + std::string(SDL_GetError()), LOG_ERROR);
            exit(1);
        }

        // Set render scaling
        // SDL_RenderSetScale(SDLRenderer, RENDER_SCALE, RENDER_SCALE);

        // Set the SDL blend mode to BLEND
        if (SDL_SetRenderDrawBlendMode(SDLRenderer, SDL_BLENDMODE_BLEND) != 0)
        {
            Log("Failed to set SDL blend mode: " + std::string(SDL_GetError()), LOG_ERROR);
            exit(1);
        }

        // Hide the OS cursor image
        SDL_ShowCursor(SDL_DISABLE);

        // Open the SDL window
        SDL_ShowWindow(SDLWindow);
    }

    void SDL2Renderer::Close()
    {
        Log("Closing SDL GPU renderer...", LOG_INFO);

        for (auto t : textureMap)
        {
            SDL_DestroyTexture(t.second);
        }

        textureMap.clear();
    }

    void SDL2Renderer::Prepare()
    {
        SDL_SetRenderDrawColor(SDLRenderer, ColorBlack.red, ColorBlack.green, ColorBlack.blue, ColorBlack.alpha);
        SDL_RenderClear(SDLRenderer);
    }

    void SDL2Renderer::Render()
    {
        SDL_RenderPresent(SDLRenderer);
    }

    void SDL2Renderer::SetCameraPosition(float x, float y)
    {
        CameraOffsetX = x;
        CameraOffsetY = y;
    }

    float SDL2Renderer::GetCamX()
    {
        return CameraOffsetX;
    }

    float SDL2Renderer::GetCamY()
    {
        return CameraOffsetY;
    }

    float SDL2Renderer::GetResolutionX()
    {
        return ResolutionW;
    }

    float SDL2Renderer::GetResolutionY()
    {
        return ResolutionH;
    }

    void SDL2Renderer::DrawRectangle(float x, float y, float w, float h, Color color) const
    {
        SDL_Color c = {color.red, color.green, color.blue, color.alpha};
        SDL_SetRenderDrawColor(SDLRenderer, c.r, c.g, c.b, c.a);
        auto r = TransformRect(x, y, w, h);
        SDL_RenderFillRect(SDLRenderer, &r);
    }

    void SDL2Renderer::DrawTexture(AssetKey textureKey, float x, float y, float w, float h, bool absolute) const
    {
        SDL_Texture *texture = nullptr;

        auto t = textureMap.find(textureKey);

        if (t == textureMap.end())
        {
            auto image = AssetManager.GetTexture(textureKey);
            texture = SDL_CreateTextureFromSurface(SDLRenderer, image);
            textureMap.insert({textureKey, texture});
        }
        else
        {
            texture = t->second;
        }

        auto r = TransformRect(x, y, w, h, absolute);
        SDL_RenderCopy(SDLRenderer, texture, nullptr, &r);
    }

    void SDL2Renderer::DrawFont(std::string text, AssetKey fontKey, Color color, float x, float y, float scale, bool absolute) const
    {
        SDL_Color fontColor = {color.red, color.green, color.blue, color.alpha};

        // TODO: unchanging text elements could be cached instead of rebuilt every frame

        auto font = AssetManager.GetFont(fontKey);
        auto surface = TTF_RenderText_Blended(font, text.c_str(), fontColor);
        auto texture = SDL_CreateTextureFromSurface(SDLRenderer, surface);

        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

        auto r = TransformRect(x, y, w * scale, h * scale, absolute);

        SDL_RenderCopy(SDLRenderer, texture, nullptr, &r);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }

} // namespace cm