#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "../basesprite.hpp"

class SDL3Sprite : public BaseSprite 
{
    public:
        SDL3Sprite(std::string path, std::string type);
        ~SDL3Sprite() override;

        void init(std::string path, std::string type = "none") override;
        void render() override;
    private:
        SDL_Texture *texture;
};