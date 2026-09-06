#include <algorithm>

#include "spritemanager.hpp"
#include "funkinsprite.hpp"

SpriteManager sprites;

void SpriteManager::add(FunkinSprite* sprite)
{
    dasprites.push_back(sprite);
}

void SpriteManager::remove(FunkinSprite* sprite)
{
    dasprites.erase(std::remove(dasprites.begin(), dasprites.end(), sprite), dasprites.end());
}

void SpriteManager::clear()
{
    for (FunkinSprite* sprite : dasprites)delete sprite;
    dasprites.clear();
}

void SpriteManager::update(float elapsed)
{
    for (FunkinSprite* sprite : dasprites)
    {
        sprite -> update(elapsed);
    }
}

void SpriteManager::render()
{
    for (FunkinSprite* sprite : dasprites)
    {
        sprite -> render();
    }
}