#include <algorithm>

#include "spritemanager.hpp"
#include "funkinsprite.hpp"

void SpriteManager::add(FunkinSprite* sprite)
{
    sprites.push_back(sprite);
}

void SpriteManager::remove(FunkinSprite* sprite)
{
    sprites.erase(std::remove(sprites.begin(), sprites.end(), sprite), sprites.end());
}

void SpriteManager::clear()
{
    for (FunkinSprite* sprite : sprites)delete sprite;
    sprites.clear();
}

void SpriteManager::update(float elapsed)
{
    for (FunkinSprite* sprite : sprites)
    {
        sprite -> update(elapsed);
    }
}

void SpriteManager::render()
{
    for (FunkinSprite* sprite : sprites)
    {
        sprite -> render();
    }
}