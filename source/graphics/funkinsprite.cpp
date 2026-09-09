#include "funkinsprite.hpp"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "sdl3/sdl3sprite.hpp"
#endif

FunkinSprite::FunkinSprite(const std::string& path, const std::string& type)
{
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
    sprite = std::make_unique<SDL3Sprite>(path, type);
    #endif
}

void FunkinSprite::update(float elapsed)
{
    sprite -> update(elapsed);
}

void FunkinSprite::render()
{
    sprite -> render();
}

void FunkinSprite::addAnim(const std::string& name, const std::string& prefix, float fps, bool looped, bool flipX, bool flipY)
{
    sprite -> addAnim(name, prefix, fps, looped, flipX, flipY);
}

void FunkinSprite::addAnim(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps, bool looped, bool flipX, bool flipY)
{
    sprite -> addAnim(name, prefix, indices, fps, looped, flipX, flipY);
}

void FunkinSprite::playAnim(const std::string& name)
{
    sprite -> playAnim(name);
}

SpriteRenderParams& FunkinSprite::getParams()
{
    return sprite -> stuff;
}

float FunkinSprite::getWidth()
{
    return sprite -> getWidth();
}

float FunkinSprite::getHeight()
{
    return sprite -> getHeight();
}