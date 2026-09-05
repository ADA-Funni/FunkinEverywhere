#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "../basesprite.hpp"

class SDL3Sprite : public BaseSprite 
{
  public:
    SDL_Texture *texture = nullptr;
    
    ~SDL3Sprite() override;

    bool SDL3Sprite(std::string tag, std::string path, std::string type);
    void render(SpriteRenderParams &params);
};