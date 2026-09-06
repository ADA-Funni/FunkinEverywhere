#include "funkinsprite.hpp"

#include "sdl3/sdl3sprite.hpp"

FunkinSprite::FunkinSprite(const std::string& path, const std::string& type)
{
    sprite = std::make_unique<SDL3Sprite>(path, type);
}

void FunkinSprite::update(float elapsed)
{
    sprite -> update(elapsed);
}

void FunkinSprite::render()
{
    sprite -> render();
}

void FunkinSprite::playAnim(const std::string& name, float fps, bool loop)
{
    sprite -> playAnim(name, fps, loop);
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