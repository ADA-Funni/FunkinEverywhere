#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "../basesprite.hpp"

class SDL3Sprite : public BaseSprite 
{
    public:
        SDL3Sprite(const std::string& path, const std::string& type = "none");
        ~SDL3Sprite() override;

        void init(const std::string& path, const std::string& type) override;
        void render() override;
    private:
        SDL_Texture *texture;
};