#include "basesprite.hpp"

BaseSprite::~BaseSprite() 
{
    
}

void BaseSprite::render(SpriteRenderParams &params) 
{
    
}

int BaseSprite::getWidth() { return sprData.width; }
int BaseSprite::getHeight() { return sprData.height; }