#include <SDL3/SDL.h>
#include <string>

#include "basesprite.hpp"
#include "../../rendering/sdl3/window.hpp"

SDL3Sprite::SDL3Sprite(std::string tag, std::string path, std::string type) 
{
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, sprData.width, sprData.height);

    if (!texture) 
    {
        return nonstd::make_unexpected("Failed to create texture: " + std::string(SDL_GetError()));
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    sprData.pixels =

    if (!SDL_UpdateTexture(texture, nullptr, sprData.pixels, sprData.pitch)) 
    {
        return nonstd::make_unexpected("Failed to update texture: " + std::string(SDL_GetError()));
    }
}

SDL3Sprite::~SDL3Sprite() 
{
    SDL_DestroyTexture(texture);
}

void SDL3Sprite::render(ImageRenderParams &params) 
{
    const float &x = params.x;
    const float &y = params.y;
    const double angle = Math::radiansToDegrees(params.angle);
    const float &scaleX = params.scaleX;
    const float &scaleY = params.scaleY;
    const float &opacity = params.alpha;
    SDL_FlipMode flip = params.flipX ? params.flipY ? SDL_FLIP_HORIZONTAL_AND_VERTICAL : SDL_FLIP_HORIZONTAL : params.flipY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;

    SDL_FRect renderRect;
    renderRect.w = sprData.width / sprData.scale * scaleX;
    renderRect.h = sprData.height / sprData.scale * scaleY;

    SDL_FRect subRect;
    if (params.subrect != nullptr) 
    {
        subRect = {
            .x = static_cast<float>(params.subrect->x),
            .y = static_cast<float>(params.subrect->y),
            .w = static_cast<float>(params.subrect->w),
            .h = static_cast<float>(params.subrect->h)};
    }
    else 
    {
        subRect = {
            .x = 0.0f,
            .y = 0.0f,
            .w = static_cast<float>(sprData.width),
            .h = static_cast<float>(sprData.height)};
    }

    if (centered) 
    {
        renderRect.x = x - (renderRect.w / 2);
        renderRect.y = y - (renderRect.h / 2);
    } 
    else 
    {
        renderRect.x = x;
        renderRect.y = y;
    }

    Uint8 alpha = static_cast<Uint8>(opacity * 255);
    SDL_SetTextureAlphaMod(texture, alpha);

    const SDL_FPoint center = {renderRect.w / 2.0f, renderRect.h / 2.0f};

    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_RenderTextureRotated(renderer, texture, &subRect, &renderRect, angle, &center, flip);
}