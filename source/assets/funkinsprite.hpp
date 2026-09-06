#pragma once
#include <memory>
#include <string>

#include "basesprite.hpp"

class FunkinSprite
{
    friend class SpriteManager;

    private:
        std::unique_ptr<BaseSprite> sprite;

    public:
        FunkinSprite(const std::string& path, const std::string& type = "none");

        void update(float elapsed);
        void render();

        void playAnim(const std::string& name);

        SpriteRenderParams& getParams();

        float getWidth();
        float getHeight();
};